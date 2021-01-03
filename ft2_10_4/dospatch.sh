#!/bin/sh
# patch for bug #: 59489
# https://savannah.nongnu.org/bugs/?func=detailitem&item_id=59489
find . -name "*.[c|h]" -exec sed -i "s/compiler-macro/compiler/" {} \;
find . -name "*.[c|h]" -exec sed -i "s/integer-types/integer/" {} \;
find . -name "*.[c|h]" -exec sed -i "s/public-macros/public-m/" {} \;
find . -name "*.[c|h]" -exec sed -i "s/mac-support/mac-supp/" {} \;
find . -name "*.[c|h]" -exec sed -i "s/wofftypes/wofftype/" {} \;
find . -name "*.[c|h]" -exec sed -i "s/cffotypes/cffootype/" {} \;
find . -name "*.[c|h]" -exec sed -i "s/woff2tags/woff2tag/" {} \;

if [ -e "./src/sfnt/woff2tags.c" ]; then
mv ./src/sfnt/woff2tags.c ./src/sfnt/woff2tag.c
fi
