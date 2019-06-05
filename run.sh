echo "building wyskr..."
echo ""

# run on successful build
if make clean && make ; then
    echo ""
    echo "build succeeded!"
    echo ""

    ./bin/wyskr
fi
