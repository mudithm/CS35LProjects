#!/usr/local/cs/bin/python3

import random, sys
from optparse import OptionParser

class shuf:
    def __init__(self, arrayOrFile = 0, filename=""):
        if arrayOrFile == 1:
            self.lines = filename
        elif filename == "-" or filename == "":
            self.lines = sys.stdin.readlines()
        else:
            try:
                f = open (filename, 'r')
                self.lines = f.readlines()
                f.close()
            except FileNotFoundError as e:
                sys.stderr.write("shuf.py: {0}: No such file or directory\n".
                                 format(filename))
                sys.exit(2)
                
    def randomize(self):
        if len(self.lines) == 0:
            return ""
        out = list(self.lines)
        random.shuffle(out)
        return out

    def chooseline(self):
        if len(self.lines) == 0:
            sys.stderr.write("shuf.py: no lines to repeat\n")
            sys.exit(2)
        return random.choice(self.lines)


# callback functions

def i_seen(option, opt_str, value, parser):
    if parser.values.COUNT == None:
        parser.values.i_first = True
        parser.values.n_first = False
    setattr(parser.values, option.dest, value)

def n_seen(option, opt_str, value, parser):
    if parser.values.LO_HI == "":
        parser.values.n_first = True
        parser.values.i_first = False
    setattr(parser.values, option.dest, value)
    
def main():
    
    try:
        version_msg = "%prog 2.0"
        usage_msg = """%prog [OPTION]... [FILE]
        or: shuf.py -i LO-HI [OPTION]...

        Write a random permutation of the input lines to standarad output.

        With no FILE, or when FILE is -, read standard input."""

        parser = OptionParser(version=version_msg,
                              usage=usage_msg)
 
        # Options for shuf:

        # Input Range
        parser.add_option("-i", "--input-range",
                          action="callback", callback=i_seen, type="string", nargs=1, dest="LO_HI", default="",
                          help="treat each number LO through HI as an input line"
        )

        parser.add_option("-n", "--head-count",
                          action="callback", callback=n_seen, type="string", nargs=1, dest="COUNT", default=None, 
                          help="output at most COUNT lines")
        

        parser.add_option("-r", "--repeat",
                          action="store_true", dest="REPEAT", default=False,
                          help="output lines can be repeated") 
                      
        options, args = parser.parse_args(sys.argv[1:])
        

        # error checking:

        # n before i
        if options.COUNT != None and parser.values.n_first:
            if options.COUNT != None:
                try:
                    int(options.COUNT)
                except ValueError as e:
                    parser.exit(2, "shuf.py: invalid line count '{0}'\n".
                            format(options.COUNT))

                if int(options.COUNT) < 0:
                    parser.exit(2, "shuf.py: invalid line count: '{0}'\n".
                         format(options.COUNT))

            if options.LO_HI != "":
                try:
                    emg = options.LO_HI
                    inpe = options.LO_HI.split('-', 1)
            
                    emg = inpe[0]
                    loo = int(emg)
            
                    emg = inpe[1]
                    hii = int(emg)

                    if (loo - hii) > 1:
                        parser.exit(2, "shuf.py: invalid range: '{0}'\n". 
                             format(options.LO_HI))
                except ValueError as e:
                    parser.exit(2, "shuf.py: invalid input range: '{0}'\n".
                          format(emg))
                if len(args) > 0:
                    parser.exit(2, "shuf.py: extra operand '{0}'\nTry shuf.py --help for more information.\n".
                         format(args[0]))
        # i before n
        else:
        
            if options.LO_HI != "":
                try:
                    emg = options.LO_HI
                    inpe = options.LO_HI.split('-', 1)
            
                    emg = inpe[0]
                    loo = int(emg)
            
                    emg = inpe[1]
                    hii = int(emg)

                    if (loo - hii) > 1:
                        parser.exit(2, "shuf.py: invalid range: '{0}'\n". 
                             format(options.LO_HI))
                except (ValueError, IndexError) as e:
                    parser.exit(2, "shuf.py: invalid input range: '{0}'\n".
                          format(emg))
                if len(args) > 0:
                    parser.exit(2, "shuf.py: extra operand '{0}'\nTry shuf.py --help for more information.\n".
                         format(args[0]))

            if options.COUNT != None:
                try:
                    int(options.COUNT)
                except ValueError as e:
                    parser.exit(2, "shuf.py: invalid line count '{0}'\n".
                            format(options.COUNT))

                if int(options.COUNT) < 0:
                    parser.exit(2, "shuf.py: invalid line count: '{0}'\n".
                         format(options.COUNT))     



        
        if options.COUNT != None:
            if int(options.COUNT) == 0:
                return
            elif int(options.COUNT) < 0:
                    parser.exit(2, "invalid line count: '{0}'\n".
                             format(options.COUNT))
            else:
                line_count = int(options.COUNT)
        else:
            line_count = -1
        
        if options.LO_HI != "": 
            try:
                emsg = options.LO_HI
                input_range = options.LO_HI.split('-', 1)
            
                if len(input_range) != 2:
                    parser.exit(2, "shuf.py: length error: invalid input range '{0}'\n".
                             format(options.LO_HI))
                emsg = input_range[0]
                lo = int(input_range[0])
            
                emsg = input_range[1]
                hi = int(input_range[1])

                if lo == hi:
                    print (lo)
                    return
                elif (lo - hi) > 1:
                    parser.exit(2, "shuf.py: invalid range: '{0}'\n".
                             format(options.LO_HI))
                elif (lo - hi) == 1:
                    return

                hi += 1

                
                
                    
            except ValueError as e:
                parser.exit(2, "shuf.py: invalid input range: '{0}'\n".
                          format(emsg))
            if len(args) > 0:
                parser.exit(2, "shuf.py: extra operand '{0}'\nTry shuf.py --help for more information.\n".
                         format(args[0]))

            input_file = shuf(1, range(lo, hi))

                
        elif len(args) == 0:
            input_file = shuf(0,"")
        elif len(args) > 1:
            parser.exit(2, "shuf.py: extra operand '{0}'\n".
                         format(args[1]))
        else:
            input_file = shuf(0,args[0])

        try:            
            if (options.REPEAT):
                if options.LO_HI != "":
                    i = 0
                    while i != line_count:
                        print(input_file.chooseline())
                        i+=1
                else:
                    
                    i=0
                    while i != line_count:
                        sys.stdout.write(input_file.chooseline())
                        i+=1
                return
                
            lines = input_file.randomize()    

            if line_count != -1:
                line_count = min(line_count, len(lines))
            else:
                line_count = len(lines)
            if options.LO_HI != "":
                for i in range(line_count):
                    print (str(lines[i]))
            else:
                for i in range(line_count):
                    sys.stdout.write(str(lines[i]))
                
        except IOError as e:
            errno, strerror=e.args
            parser.exit(2, "shuf.py: I/0 error({0}): {1}\n".
                     format(errno, strerror))


    
    except KeyboardInterrupt as e:
        print("")

if __name__ == "__main__":
    main()
    
