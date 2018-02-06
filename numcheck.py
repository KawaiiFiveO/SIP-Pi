#!/usr/bin/env python

# read the file and check, if the number is contained within.
# Special precaution when chenging stuff: The first character printed must be the result: '1' = yes other = no

from time import gmtime, strftime
import sys
import os

filename = 'numbers.txt'
logfile = 'calls.log'

def log(s):
    actime = strftime("%Y-%m-%d %H:%M:%S", gmtime())
    with open(logfile,'a') as myFile:
        myFile.write("# "+actime+" "+s+"\n")

if 2 != len(sys.argv):
    print '0'
    print 'Number of arguments:', len(sys.argv), 'arguments.'
    print 'Argument List:', str(sys.argv)
    print 'call with one argument (the number to be searched)'
    sys.exit(1)

if not os.path.exists(filename):
    print '0'
    print 'file ' + filename + ' does not exist. Creating it for you.'
    with open(filename, 'w') as f:
        f.write("# Numbers file for numcheck.py\n")
        f.write("# one number per line, # makes a comment\n")
        f.write("080012345678 # your test number\n")
        sys.exit(1)
try:
    f = open(filename, mode='r')
except IOError as e:
    print '0'
    print "I/O error({0}): {1}".format(e.errno, e.strerror)
    print 'Error reading File ' + filename + '.'
    sys.exit(1)

with f:
    # now we read the file
    lines = f.readlines()
    f.close()

for line in lines:
    if line[0] not in '#\n':  # skip commented and empty lines
        line = line.replace("\n", " ")
        line = line.replace("#", " ")
        sline = line.split(" ", 1)
        # print sline must never print in production use - the first char printed counts!
        if sys.argv[1].startswith(sline[0]):
            print "1 Number found!"
            log(str(sys.argv[1]) + " found as " + sline[0])
            sys.exit(0)

# at end of execution:
print "0 Number not found!"
log(str(sys.argv[1]) + " not found.")
sys.exit(0)
