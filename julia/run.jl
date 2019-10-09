"""Template programming is a sort of metaprogramming where you fill
in the blanks, but most parts of the code are very similar."""

# Problem1
for (name,op) in [(:add, :+), (:sub, :-), (:mul, :*)]
  # Create a function that is named for example add and returns the
  # sum of its two arguments
  @eval $name(x,y) = $op(x,y) 
end

@assert 3 == add(1, 2)
@assert -1.0 == sub(1.0, 2.0)
@assert "abc" == mul("ab", "c")

"""Reflective programming often has to do with accessing or creating functions
at runtime, but it is so similar to template programming that you could
try to delete a function instead."""

module Problem2
  f(a::Int) = 1
  f(a::Any) = 2
end

# TODO: Delete the method f(a::Int) so that f(1) returns the value 2 instead of 1
m = which(Problem2.f,(Int,))
Base.delete_method(m)

@assert 2 == Problem2.f(1)

# Problem3
# TODO: Make an until block for Julia, similar to do {} while (cond); in C
#
# Make sure that any assertions and error-messages refer to lines in the original code.
# Hint: You can access a hidden input __source__ in a macro and use that to replace source information.
# By having the macro in a separate file, you can check source locations that match dowhile.jl and replace them with __source__.
include("dowhile.jl") # Modify the macro in dowhile.jl
function testDoWhile()
  local a = 5
  @doWhile begin
    @assert a < 18
    a += 1
    println(a)
  end a==100
end
testDoWhile()
