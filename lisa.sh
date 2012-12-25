# Replace with your absolute path to the root of lisa tree
# tp-master tree is at $HOME/w/t2_cur/tinyos-2.x
export LISA_ROOT="${HOME}/w/lisa"
export TOSMAKE_PATH="$TOSMAKE_PATH $LISA_ROOT/support/make"

export TOSROOT=$HOME/w/t2_cur/tinyos-2.x
export TOSDIR=$TOSROOT/tos
export MAKERULES=$TOSROOT/support/make/Makerules
export CLASSPATH=.:$TOSROOT/support/sdk/java/tinyos.jar
export PYTHONPATH=$TOSROOT/support/sdk/python:$PYTHONPATH
