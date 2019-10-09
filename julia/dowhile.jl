macro doWhile(block, cond)
  println("__source__ ", __source__) # __source__ #= /home/jarye821/Repositories/tdde45-lab5/julia/run.jl:39 =#
  println("cond ", cond)
  println("block ", block)
  
  println("Base.source_path() ", Base.source_path()) # /home/jarye821/Repositories/tdde45-lab5/julia/run.jl
  println("@__FILE__ ", @__FILE__) # /home/jarye821/Repositories/tdde45-lab5/julia/dowhile.jl

  res = quote
  
  while true
    $(esc(block))
    println(block)
    println(esc(block))
    println($(esc(block)))
    local val = $(esc(cond))

    println(cond)
    println(esc(cond))
    println($(esc(cond)))    
    
      if val
        break
      end
    end
  end

  offset = 0
  local oldLineNumber = __source__.line
  
  for arg in split(string(res.args[2]), "\n")
    if occursin(@__FILE__, arg)
      local s = replace(arg, string(@__FILE__) => Base.source_path())
      s = split(s, ":")[1]
      println(s, ":", string(oldLineNumber + offset))
      # println(replace(arg, __FILE__ => split(__source__, ":")[1]), ":", )
      offset = offset + 1
    else
      println(arg)
    end
  end

end
  