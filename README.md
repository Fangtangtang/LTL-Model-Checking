# LTL-Model-Checking
CS3959 course project

## Prerequisite
### Antlr 4
1. Download ANTLR:
I use `antlr-4.12.0-complete.jar` for this project which can be found in `https://github.com/antlr/website-antlr4/tree/gh-pages/download`.

2. [Compile and install C++ runtime support](https://github.com/antlr/antlr4/tree/master/runtime/Cpp#compiling-on-linux)

   ```shell
   git clone git@github.com:antlr/antlr4.git antlr4
   cd antlr4/runtime/Cpp 
   mkdir build && mkdir run && cd build
   cmake .. -DANTLR_JAR_LOCATION=path/to/antlr-4.12.0-complete.jar
   make
   sudo DESTDIR=path/to/install/antlr4/runtime/Cpp make install
   ```

The install directory `DESTDIR` should be compatiable with `ANTLR4_RUNTIME_PATH` in [`CMakeList.txt`](src/CMakeLists.txt).

## Run
Input file for transition system: `./testcases/TS.txt`.

Input file for LTL formula: `./testcases/LTL-formulas.txt`.

```shell
cd src
mkdir -p build && cd build  
cmake ..  
make      
./LTL_Model_Checking
```

You can find the output result in terminal.

## Implementation
### Parser
We use ANTLR4 to generate a parser from [`LTL.g4`](./src/parser/LTL.g4). The parser processes each formula using the visitor pattern. Specifically, we traverse the parse tree with `FormulaBuilder`, a subclass of `LTLBaseVisitor`, which is defined in [`formula.hpp`](./src/utils/formula.hpp). This class constructs instances of LTL formulas. After parsing, we further transform the formulas into their normal form.

### GNBA Construction from LTL Formula
We construct the GNBA using the algorithm described in Theorem 5.37 (page 278 of *Principles of Model Checking*). The constructor is implemented as follows:  

```c++
GNBA(const std::shared_ptr<FormulaBase> &formula) : phi(formula) {
  getClosureAndAP();
  buildAlphabet();
  buildStates();
  buildTransition();
}
``` 

The function `getClosureAndAP()` computes $closure(\phi)$ and collects the `AtomicPropositions` used in $\phi$. The function `buildAlphabet()` constructs the alphabet based on the collected atomic propositions. The function `buildStates()` generates the states of the GNBA, which are elementary sets of formulae. Finally, `buildTransition()` defines the transitions between these states.  

Additional implementation details are available in [`automata.hpp`](./src/utils/automata.hpp).

### NBA Construction from GNBA
We construct the NBA from GNBA using the algorithm described in Theorem 4.56 (page 195 of *Principles of Model Checking*). 

The theorem assumes that $\mathcal{F} \neq \emptyset$. If $\mathcal{F}$ in the GNBA is $\empty$, we apply a simple transformation by replacing $\mathcal{F}$ with $\mathcal{F}'=\mathcal{F} \cup \{Q\}$.

Additional implementation details can be found in [`automata.hpp`](./src/utils/automata.hpp).

### [Product Construction](./src/utils/check.hpp)
We construct `TransitionSystemProductNBA`, the product of the input Transition System and NBA, by Definition 4.62 (page 200 of *Principles of Model Checking*)

Since we collect only the atomic propositions used in the formula during automata construction, any unused atomic propositions are treated as "don't care" when determining initial states and transitions.

Additional implementation details can be found in [`check.hpp`](./src/utils/check.hpp).

### Nested DFS
The `check()` function for each `TransitionSystemProductNBA` uses the nested depth-first search algorithm described on page 211 of *Principles of Model Checking*.  

For more details, refer to the implementation in [`check.hpp`](./src/utils/check.hpp).
