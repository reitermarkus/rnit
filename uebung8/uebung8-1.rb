#!/usr/bin/env ruby

graph1 = {
  A: {B: [:B, :D], O: [:B]},
  B: {B: [:A, :D], O: [:A, :C]},
  C: {B: [:B],     O: [:D, :E]},
  D: {B: [:C, :E], O: [:A, :B]},
  E: {B: [:C],     O: [:D]},
}

graph2 = {
  A: {B: [:E],     O: [:B, :C]},
  B: {B: [:A],     O: [:C]},
  C: {B: [:A, :B], O: [:D]},
  D: {B: [:C],     O: [:E]},
  E: {B: [:D],     O: [:A]},
}

graph_vorlesung = {
  A: {B: [:D, :E, :H, :F, :G], O: [:B, :C]},
  B: {B: [:A],                 O: [:D, :E]},
  C: {B: [:A],                 O: [:F, :G]},
  D: {B: [:B],                 O: [:A, :H]},
  E: {B: [:B],                 O: [:A, :H]},
  F: {B: [:C],                 O: [:A]},
  G: {B: [:C],                 O: [:A]},
  H: {B: [:D, :E],             O: [:A]}
}

def page_rank_k(key, graph, previous_iterations)
  return Rational(1, graph.size) if previous_iterations.empty?

  graph[key][:B].inject(0.to_r) { |sum, backlinking_page|
    sum + previous_iterations.last[backlinking_page] / graph[backlinking_page][:O].size
  }
end

def page_rank(graph, iterations: 100)
  iterations.times.inject([]) { |ary|
    ary << graph.keys.each_with_object({}) { |key, obj|
      obj[key] = page_rank_k(key, graph, ary)
    }
  }
end

def page_ranks_to_latex(page_ranks)
  keys = page_ranks.first.keys

  lines = []

  lines << "\\begin{tabular}{|l|*{#{keys.size}}{c|}}"

  lines << '  \hline'
  lines << "  Iteration & #{keys.join(" & ")} \\\\"
  lines << '  \hline'

  page_ranks.each_with_index do |iteration, i|
    lines << "  #{i + 1} & #{iteration.values.map { |rat| "$\\frac{#{rat.numerator}}{#{rat.denominator}}$"}.join(' & ')} \\\\"
    lines << '  \hline'
  end

  lines << '\end{tabular}'

  lines.join("\n")
end

# puts page_ranks_to_latex page_rank(graph_vorlesung, iterations: 4)
# puts
puts page_ranks_to_latex page_rank(graph1, iterations: 8)
puts
puts page_ranks_to_latex page_rank(graph2, iterations: 8)
