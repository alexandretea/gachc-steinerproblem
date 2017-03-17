# gachc-steinerproblem
a Genetic Algorithm (CHC) solving the Generalised Steiner Problem

For educational purposes

https://pdfs.semanticscholar.org/f595/f85669d5ec20ce9639d899329e79efbe353a.pdf

# TODO
- graph id_to_string to std::to_string specialisation?
- same as previous with IStringRepresentation?
- discard non-feasible solutions vs. force them to be feasible

# dependencies
- https://github.com/nlohmann/json

# bottlenecks
- feasbility check = dfs
