mkdir -p $HOME/.local/bin
BLOB=`echo $PATH |grep .locals |wc -l`

if [ $BLOB = 0 ]
then
    echo PATH=\"$HOME/.local/bin:\${PATH}\"  >> $HOME/.zprofile
    echo export PATH >> $HOME/.zprofile
fi
