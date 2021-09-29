# Unix commands for Windows

Shifting from linux/mac from windows can be stressful given the lack of cli apps in windows. Although latest powershell gives us basic commands like ls, cat they are nowhere close to their unix counterparts. These are some basic implementation of unix commands for windows. These are no way close to original implementation. Also written in good old C. 

### Installing

To install the commands clone this repo and run this powershell script. Please make sure you have <a href="https://stackoverflow.com/questions/58524451/how-to-run-powershell-script-from-ps1-file"> enabled </a> powershell to run external scripts. And lets be honest who even uses command prompt

```powershell
.\installer.ps1
```

Unfortunately ls, pwd and cat have powershell aliases if you don't disable them you have to use `ls.exe` to run our ls. Though the installer script removes the aliases, to remove them properly please append the following into your powershell profile (Please create one if you don't have any)

```powershell
remove-item alias:ls
remove-item alias:pwd
remove-item alias:cat
```