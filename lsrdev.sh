# Replace with your absolute path to the root of lsrdev tree
# tp-master tree is at $HOME/w/tos_cur/tinyos-2.x
export LSRDEV_ROOT="${HOME}/w/lsrdev"
export TOSMAKE_PATH="$TOSMAKE_PATH $LSRDEV_ROOT/support/make"

export TOSROOT=$HOME/w/tos_cur/tinyos-2.x
export TOSDIR=$TOSROOT/tos
export MAKERULES=$TOSROOT/support/make/Makerules
export CLASSPATH=.:$TOSROOT/support/sdk/java/tinyos.jar
export PYTHONPATH=$TOSROOT/support/sdk/python:$PYTHONPATH
