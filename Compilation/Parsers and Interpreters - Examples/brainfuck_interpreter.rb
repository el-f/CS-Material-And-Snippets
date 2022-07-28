def brain_fuck(code, input)
  match, stack = [], []
  code.chars.each_with_index do |c, i|
    if c == '['
      stack.push(i)
    elsif c == ']'
      j = stack.pop
      match[i], match[j] = j, i
    end
  end
  input = input.chars.to_a
  output = ''
  m = Hash.new(0)
  data_pointer, cmd_pointer = 0, 0
  loop do
    break if cmd_pointer >= code.size
    case code[cmd_pointer]
    when '>' then data_pointer += 1
    when '<' then data_pointer -= 1
    when '+' then m[data_pointer] = (m[data_pointer] + 1) % 256
    when '-' then m[data_pointer] = (m[data_pointer] - 1) % 256
    when '.' then output << m[data_pointer].chr
    when ',' then m[data_pointer] = (input.shift || 0).ord
    when '[' then cmd_pointer = match[cmd_pointer] if m[data_pointer].zero?
    when ']' then cmd_pointer = match[cmd_pointer] unless m[data_pointer].zero?
    else
      raise "Unknown instruction: #{code[cmd_pointer]}"
    end
    cmd_pointer += 1
  end
  output
end