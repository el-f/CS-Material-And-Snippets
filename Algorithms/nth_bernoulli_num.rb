def bernoulli_number(n)
  if n % 2 != 0 && n != 1
    return 0
  end
  b = [Rational(1, 1)]
  pascal = [[1], [1, 1]]
  n.times do |i|
    pascal.push([1].concat((0..i).map { |j| pascal[i + 1][j] + pascal[i + 1][j + 1] }).concat([1]))
    b.push(-Rational((0..i).map { |j| pascal[i + 2][j] * b[j] }.reduce(:+), i + 2))
  end
  b.last
end