def get_symbols(addr2name, bin)
  symbols = {}
  `#{addr2name} #{bin}`.each_line do |l|
    s = l.split(' ')
    symbols[s[0].hex] = s[1]
  end
  symbols
end

def dotlines(tracefile, symbols)
  stack = []
  lines = {}
  cnt = 0
  start = false
  File.open(tracefile) do |f|
    f.readlines.each do |l|
      name = symbols[l[1..-1].hex]
      if l[0] == 'E'[0]
        line = "#{stack[-1]} -> #{name}"
        if stack.size > 0
          lines[line] = [] if lines[line] == nil
          lines[line] << cnt+=1 
        end
        stack.push name
      else
        stack.pop
      end
    end
  end
  lines
end

def puts_dot_format(lines)
  puts "digraph instest {"
  lines.keys.each do |k|
    if lines[k].length <= 3
      puts "#{k} [label=\"#{lines[k].join(',')}\"];"
    else
      puts "#{k} [label=\"#{lines[k][0..2].join(',')} and #{lines[k].length-3}calls\"];"
    end
  end
  puts "}"
end

if $0 == __FILE__
  raise ArgumentError if ARGV.size != 1
  ADDR2NAME = './addr2name'
  BINFILE = ARGV[0]
  TRACEFILE = File.join(File.dirname(BINFILE), 'trace.txt')  
  symbols = get_symbols(ADDR2NAME, BINFILE)
  lines = dotlines(TRACEFILE, symbols)
  puts_dot_format(lines)
end
