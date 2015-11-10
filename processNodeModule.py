# coding=utf-8
import os


def renameDir(curDir):
        # 获得当前目录下的所有文件、文件夹
        curDirs = os.listdir(curDir)
        print os.listdir(curDir)
        index = 0
        newDirs = []
        newDir = ''
        # 切换为当前文件夹
        os.chdir(curDir)

        # 遍历当前目录下的所有文件
        for single_dir in curDirs:
                # 只处理文件夹
                if os.path.isdir(single_dir):
                        newDir = 'a'+str(index)
                        # python list 没有 push，用 append 代替
                        newDirs.append(newDir)
                        os.rename(single_dir, newDir)
                        index += 1

        # 递归处理子文件夹
        for new_single_dir in newDirs:
                # 如果当前
                child_dir = os.path.join(curDir, new_single_dir)
                renameDir(child_dir)

        return

renameDir('D:\\code\\fountain-new\\node_modules1')
