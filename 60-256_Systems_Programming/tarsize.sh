#!/bin/bash

# Author: Zach Shaver
# October 22, 2016

# Bash Script to automate compression of files from a given
# target directory to a destination directory, that exceed. 
# a given size. Uses tar for compression to a .tar file.

# Usage: tarsize [-s size] [-t tarDir] [-d destDir] < ext_list >

# size = min size in bytes (defaults to 0 bytes)
# tarDir = directory that files are located in (defaults to current dir)
# destDir = directory to place resultant myArchive.tar file (defaults to current dir)
# ext_list = list of space seperated file extensions

# check for mandatory arguments (extension list)
if [[ $# -eq 0 ]]; then
	echo "tarsize synopsis: \"tarsize [-s size] [-t tarDir] [-d destDir] < ext_list >\""
	exit
fi

# Default target & destination
target=$PWD	
destination=$PWD
# default lower limit of 0 size so script will zip all applicable files
size=0

# options are complicated to parse, so will use the getopts tool:
# for options -s -t and -d (all have arguments) (w/ silent mode -> : at 1st pos)
while getopts ":s:t:d:" opt; do
	case $opt in
		s) # size option triggered, store if valid integer
			if [[ "$OPTARG" =~ [0-9]+ ]]; then
				size=$OPTARG
			else
				echo "The argument for option -s must be an integer."
				exit 1	
			fi	
			;; # break
		t) # target directory option triggered, store if valid & readable	
			if ! [[ -d $OPTARG ]]; then
				echo "$OPTARG is not a valid directory"
				exit 1
			elif ! [[ -r $OPTARG ]]; then			
				echo "$OPTARG is not a readable directory"
				exit 1
			else
				target=$OPTARG
			fi
			;; # break
		d) # destination option triggered, store if valid & writable
			if ! [[ -d $OPTARG ]]; then
				echo "$OPTARG is not a valid directory"
				exit 1
			elif ! [[ -w $OPTARG ]]; then			
				echo "$OPTARG is not a writable directory"
				exit 1
			else
				destination=$OPTARG
			fi
			;; # break
		\?) # invalid option (any other arg starting with "-")
			echo "-$OPTARG is not a valid option." >&2
			exit 1
			;; # break
		:) # missing argument for opt
			echo "-$OPTARG is missing it's argument." >&2
			exit 1
			;; # break
	esac
done

# Exit prematurely if no additional arguments specifying file type
if [[ $OPTIND -gt $# ]]; then
	echo "No file extensions specified."
	exit 1
fi

# create directory in destination for temporarily storing files while creating the tar
mkdir $destination/myArchive
archiveDest=$destination/myArchive

# shift argument numbers left by the amount of options, so that $1 is first filetype arg
# ex: 4 optional args -> shift args 4 to left, pushing out the 4 options
shift $(($OPTIND-1)) # OPTIND (from getopts) would be 5 in the above example

echo "Compressing the following files:"
compressionCount=0
# now can sift through filetype arguments
# starting by moving files to the archive folder
for fileType in $@; do
	# user could possibly enter ".." as a filetype argument, which is a meta-character
	# that would cause all files ending the in previous argument to be compressed
	# which could be very bad so we need to check for this condition:
	if ! [[ $fileType == ".." ]]; then
		# for each file in target directory
		for file in `ls $target`
		do
			fileSize=`more $target/$file | wc -c`
			# that ends in the given file type and has a byte size greater than given size
			if [[ "$file" =~ ^.*\.$fileType$ ]] && [[ $fileSize -gt $size ]]; then
				# move file to archiving directory
				mv $target/$file $archiveDest
				echo "  $file ($fileSize bytes)"
				((compressionCount++))		
			fi
		done 
	fi
done

# compress files in the temporary archiving directory
if [[ $compressionCount -gt 0 ]]; then
	cd $archiveDest		# go to absolute path to avoid tar "leading \ removal" errors
	tar -cf $destination/myArchive.tar `ls` 
	echo "$compressionCount files compressed to $destination/myArchive.tar"
else
	echo " No applicable files greater than $size bytes to compress." # no files compressed, let user know.
fi

# delete the temporary archiving folder
rm -rf $archiveDest
