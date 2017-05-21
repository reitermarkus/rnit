#!/usr/bin/env ruby

# Install the `rsruby` Gem:
# gem install rsruby -- --with-R-dir="$(brew --prefix r)/Frameworks/R.framework/Resources"
# or set R_HOME manually:
R_PREFIX = %x(brew --prefix r).chomp
ENV['R_HOME'] = "#{R_PREFIX}/Frameworks/R.framework/Resources"

require 'rsruby'
def R(&block)
  RSRuby.instance.instance_eval(&block)
end

R do
  puts matrix(c(1, 2), nrows = 2, ncols = 2).class

  data = sin
  plot(data)
  sleep(10)
end
