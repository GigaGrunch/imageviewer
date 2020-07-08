set -e

script_dir="$(dirname "$0")"
build_dir="$script_dir/build"
code_dir="$script_dir/code"

if [ -d "$build_dir" ]
then
	rm -r "$build_dir"
fi

mkdir "$build_dir"

cd "$build_dir"
c++ -o "imageviewer" "$code_dir/linux_imageviewer.cpp"
