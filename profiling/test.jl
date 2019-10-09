using BenchmarkTools
using Random
using Profile
using StatProfilerHTML

function f()
  lst = rand(50000)
  for i in lst
    if i > 0.99
      print("List entry ")
      print(i)
      print("\r") # The \r makes it so the terminal isn't filled
    end
  end
end

@profile f()
@time f()
x = @benchmark f()
println()
println(x)
Profile.print()
statprofilehtml()
