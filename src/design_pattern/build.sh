##########################################################################
# File Name: build.sh
# Author: baoshan
# mail: baoshanw@foxmail.com
# Created Time: 2020年03月27日 星期五 17时16分34秒
#########################################################################

#!/bin/sh

#g++ -std=c++11 -I /media/wbs/work/cplus_practice create_unittest.cc create.cc product.cc -o ../../bin/create_unittest
#g++ -std=c++11 -I /media/wbs/work/cplus_practice structure_unittest.cc structure.cc product.cc -o ../../bin/structure_unittest
g++ -std=c++11 -I /media/wbs/work/cplus_practice behavior_unittest.cc behavior.cc -o ../../bin/behavior_unittest
