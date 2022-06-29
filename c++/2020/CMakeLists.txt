cmake_minimum_required (VERSION 3.0)

include (CheckLibraryExists)

check_library_exists (dbghelp UnDecorateSymbolName "" HAVE_DBGHELP)
message(HAVE_DBGHELP ${HAVE_DBGHELP})
