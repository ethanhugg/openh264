# Run this to update the codec_ver.h at changes of api

#!/bin/sh
#

if [ "$1"x = ""x ]; then
	echo "Please input the version number as : major_ver.minor_ver.patch.reserve"
	exit 127
fi

codec_ver=`echo "$1" | egrep  "^([0-9]+[.]){3}[0-9]+$"`

if [ $? -ne 0 ]; then
	echo "Please input the version number as : major_ver.minor_ver.patch.reserve"
	exit 127
fi

revision=`git show | head -n 1`
revision=`echo $revision|cut -d' ' -f2|sed -e 's#[ ]*\(.*\)[ ]*#\1#'`
revision=${revision:0:7}

echo "//The current file is auto-generated by script: generate_codec_ver.sh" >>codec_ver.h
echo "#ifndef CODEC_VER_H" >>codec_ver.h
echo "#define CODEC_VER_H" >>codec_ver.h
echo "" >>codec_ver.h

echo "#include \"codec_app_def.h\"" >>codec_ver.h
echo "" >>codec_ver.h

fullver="$1"
major="${1%%.*}"
tmp=${1#*.}
minor="${tmp%%.*}"
tmp=${tmp#*.}
revnr="${tmp%%.*}"
tmp=${tmp#*.}
resnr="${tmp%%.*}"

echo "static const OpenH264Version g_stCodecVersion  = {$major,$minor,$revnr,$resnr};" >>codec_ver.h
echo "static const char* const g_strCodecVer  = \"OpenH264 version:$fullver\";" >>codec_ver.h
#if [ "$2"x = ""x ]; then
#echo "static const char* const g_strCodecBuildNum = \"OpenH264 revision:$revision\";" >> codec_ver.h
#else
#echo "static const char* const g_strCodecBuildNum = \"OpenH264 build:$2, OpenH264 revision:$revision\";" >> codec_ver.h
#fi
echo "" >>codec_ver.h

#define OPENH264_MAJOR 1, #define OPENH264_MINOR 2 #define OPENH264_REVISION 3 #define OPENH264_RESERVED 0
echo "#define OPENH264_MAJOR ($major)" >>codec_ver.h
echo "#define OPENH264_MINOR ($minor)" >>codec_ver.h
echo "#define OPENH264_REVISION ($revnr)" >>codec_ver.h
echo "#define OPENH264_RESERVED ($resnr)" >>codec_ver.h
echo "" >>codec_ver.h

echo "#endif  // CODEC_VER_H" >>codec_ver.h

mv -f codec_ver.h ../api/svc/codec_ver.h

# Ignore non-utf8 chars in the input
export LC_ALL=C
cat ../../openh264.rc.template | sed "s/\$MAJOR/$major/g" | sed "s/\$MINOR/$minor/g" | sed "s/\$REVISION/$revnr/g" | sed "s/\$RESERVED/$resnr/g" > openh264.rc.tmp
mv openh264.rc.tmp ../../openh264.rc
