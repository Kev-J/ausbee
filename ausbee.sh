#!/bin/sh
#
# Script used for creating a new project
#
# This file is part of AUSBEE.
#
# Copyright (C) 2015 AUSBEE Developers <ausbee@googlegroups.com>
#
# AUSBEE is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# AUSBEE is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with AUSBEE.  If not, see <http://www.gnu.org/licenses/>.

# Global variables
AUSBEE_DIR=$(dirname $0)
PROJECTS_DIR=$AUSBEE_DIR/Projects
PROJECT_TEMPLATE_MAKEFILE=$PROJECTS_DIR/Makefile.template


# Display usage function
printUsage() {
    echo "AUSBEE is a development tool for building projects based on STM32"
    echo "MCUs. AUSBEE regroup all what you need for building your project from"
    echo "your C source code to the output binary."
    echo
    echo "For further question, please contact AUSBEE Developers at"
    echo "<ausbee@googlegroups.com>"
    echo
    echo "USAGE:"
    echo
    echo "  -c PROJECT_NAME         Create a new project folder in the"
    echo "                          Projects directory."
}

# Main
if [ -z "$1" ]
then
   printUsage 
   exit -1
fi

while getopts "hc:" option
do
    case $option in
        c)
            echo -e "\e[107;30mCreating project $OPTARG\033[0m"
            mkdir -p $PROJECTS_DIR/$OPTARG
            [ $? -ne 0 ] && echo -e "\033[0;31mFailure\033[0m" && exit 1
            cp $PROJECT_TEMPLATE_MAKEFILE $PROJECTS_DIR/$OPTARG/Makefile
            [ $? -ne 0 ] && echo -e "\033[0;31mFailure\033[0m" && exit 1
            echo -e "\e[32mSuccess\033[0m"
            echo -e "Please jump to $PROJECTS_DIR/$OPTARG to start"
            ;;
        h)
            printUsage
            ;;
    esac
done

exit 0
