.PHONY: run

VERSION=1.2.0

run: ../julia/julia-$(VERSION)/bin/julia
	$< test.jl

../julia/julia-$(VERSION)/bin/julia:
	$(MAKE) -C ../julia julia-$(VERSION)/bin/julia
