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
c++ -o "imageviewer" -l SDL2 "$code_dir/linux_imageviewer.cpp"
