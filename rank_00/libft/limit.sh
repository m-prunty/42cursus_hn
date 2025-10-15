#!/bin/bash
ulimit -v 65536   # limit to 64 MB for your program only
exec "$@"
