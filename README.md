# Calipers

Calipers is a tool for modeling processor performance through *event-dependence graphs*.
Calipers takes the program's dynamic instruction trace and a configuration file containing
microarchitectural and ISA specifications of the processor. It constructs a graph that models
the dependency and latency between microarchitectural events. Calipers then calculates the
performance (cycles per instruction) and provides the breakdown of bottlenecks through graph
analysis.

For more information, please refer to our publication,
"Calipers: A Criticality-aware Framework for Modeling Processor Performance," in
*2022 International Conference on Supercomputing (ICS '22)*.
([arXiv link](https://arxiv.org/abs/2201.05884))

## Build Instructions

The code has no particular dependencies and can be built with `make`:

```sh
git clone git@github.com:microsoft/calipers.git
cd calipers
make
```

The code has been built and tested on Ubuntu 18.04.

## Usage Instructions

```sh
./calipers config_file trace_file result_file
```

Example:

```sh
cd build
./calipers ../demo/InO.cfg ../demo/sample1.trace ./result_InO.txt
./calipers ../demo/OoO.cfg ../demo/sample2.trace ./result_OoO.txt
```
## Directory Structure

- `demo`: Contains sample configuration and trace files.
Please refer to [README.md](demo/README.md) under this directory for more details.
- `src`: Contains the source code of the project:
	- `branch_predictor`: Branch prediction information can be either provided through the trace
	or obtained from a model. The models are placed in this directory. Currently, it only
	contains a *statistical model* with configurable accuracy.
	- `common`: Contains the main and utility functions as well as defined constants and
	data types.
	- `graph`: Contains the graph-based modeler and analyzer for an in-order and an out-of-order
	processor. The latter also has a memory-efficient (advanced) implementation.
	- `memory`: Load and store information can be either provided through the trace
	or obtained from a model. The models are placed in this directory. Currently, it contains
	an *ideal model* (single-cycle loads/stores), a *statistical model* (configurable load/store
	hit rate and hit/miss cycles), and a *real model* (analytical two-layer cache with
	configurable size, associativity, and load/store hit/miss cycles).
	- `trace`: Contains the trace reader/parser. Currently, the RISC-V ISA is supported.

## Contributing

This project welcomes contributions and suggestions.  Most contributions require you to agree to a
Contributor License Agreement (CLA) declaring that you have the right to, and actually do, grant us
the rights to use your contribution. For details, visit https://cla.opensource.microsoft.com.

When you submit a pull request, a CLA bot will automatically determine whether you need to provide
a CLA and decorate the PR appropriately (e.g., status check, comment). Simply follow the instructions
provided by the bot. You will only need to do this once across all repos using our CLA.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).
For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or
contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

## Trademarks

This project may contain trademarks or logos for projects, products, or services. Authorized use of Microsoft 
trademarks or logos is subject to and must follow 
[Microsoft's Trademark & Brand Guidelines](https://www.microsoft.com/en-us/legal/intellectualproperty/trademarks/usage/general).
Use of Microsoft trademarks or logos in modified versions of this project must not cause confusion or imply Microsoft sponsorship.
Any use of third-party trademarks or logos are subject to those third-party's policies.
