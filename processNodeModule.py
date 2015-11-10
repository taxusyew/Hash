# coding=utf-8
import os


def renameDir(curDir):
        # 获得当前目录下的所有文件、文件夹
        curDirs = os.listdir(curDir)
        print os.listdir(curDir)
        index = 0
        newDirs = []
        newDir  = ''
        os.chdir(curDir)
        # os.rename('D:\code\fountain-new\b', 'D:\code\fountain-new\a0')
        for single_dir in curDirs:
                if os.path.isdir(single_dir):
                        origin_dir = os.path.join(os.path.dirname(curDir), single_dir) 
                        newDir = 'a'+str(index)
                        new_dir = os.path.join(os.path.dirname(curDir), newDir)
                        # print '1', origin_dir
                        # print '2', new_dir
                        newDirs.append(newDir)
                        # os.rename(origin_dir, new_dir)
                        os.rename(single_dir, newDir)
                        index+=1
                        
        print newDirs
        for new_single_dir in newDirs:
                # for new_single_dir in curDirs:
                # child_dir = os.path.join(os.path.dirname(curDir), new_single_dir)
                child_dir = os.path.join(curDir, new_single_dir)
                # print '3',child_dir
                # os.chdir(curDir)
                renameDir(child_dir)
                # print os.listdir(child_dir)


        return

renameDir('D:\\code\\fountain-new\\node_modules1')
