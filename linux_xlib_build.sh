set -e

cd "$(dirname "$0")"

script_dir="$(pwd)"
build_dir="$script_dir/build"
code_dir="$script_dir/code"

if [ -d "$build_dir" ]
then
	rm -r "$build_dir"
fi

mkdir "$build_dir"

cd "$build_dir"
cc -g -Wall -o "imageviewer" -l X11 "$code_dir/xlib_imageviewer.c"

if [ "$1" == "run" ]
then
	"$build_dir/imageviewer"
fi
