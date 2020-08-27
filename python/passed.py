import sys

try:
    print("passed %s with %s.%s" % (sys.argv[0], sys.version_info.major,
          sys.version_info.minor))
except AttributeError:
    print("passed %s with %s.%s" % (sys.argv[0], sys.version_info[0],
          sys.version_info[1]))
