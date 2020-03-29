时间久了，我忘记如何使用git了，今天花了几个小时看了看，准备总结一下几个简单的命令：

###1.在github创建仓库，git clone到本地开发

1. 先在网站新建仓库test，勾选Initialize the repository with a README
2. 在本地执行命令

   ```shell
   git clone https://github.com/wujinjun/test.git
   ```
3. 在本地进行开发

### 2.在github创建仓库，本地上传到github

1. 先在网站新建仓库test01，不勾选Initialize the repository with a README

2. 在本地新建文件夹test01，完成以下操作

	```shell
   mkdir test01									#new dir
   cd test01			
   echo "# test01" >> README.md	#初始化一个readme
   git init											#初始化仓库
   git add README.md							#添加track文件						
   git commit -m "first commit"	#提交
   git remote add origin https://github.com/wujinjun/test01.git		#远程仓库为origin
   git push -u origin master			#将本底仓库的内容推送到远程仓库
	```
### 3. git 基本操作

```shell
git init		#初始化仓库
git status	#查看仓库状态
git add			#向暂存区添加文件
git commit	#保存仓库的历史记录
git log			#查看提交日志
git diff		#查看更改前后的差别(工作树/暂存区) 
```

### 4.分支操作

```shell
git branch 			#分支一览表
git checkout 		#切换分支
git checkout -b #创建并切换分支
git merge 			#合并分支
git log --graph #以图表方式查看分支
```

### 5.更改提交操作

```shell
git reset						#回滚历史版本
git commit --amend 	#修改提交信息
```



### 6. Pull Request操作

1. fork别人的仓库
2. git clone下来
3. 在本地创建work分支`git checkout -b work`
4. 在work分支上进行修改
5. 创建远程分支`git push origin work`

6. 登陆web页面，发送Pull Request