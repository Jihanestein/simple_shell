#include "shell.h"

int main()
{
	info_t info;
	sh_cd(&info);
	sh_help(&info);
	sh_exit(&info);

	return (0);
}

/**
  * sh_cd - change current directory
  * @info: potentiel arguements
  *
  * Return: on suceess 0
  */

int sh_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd error msg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* store return value*/
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "cd cannot be done to");
		_eputs(info->argv[1]); _eputchar('\n');
	}
	else
	{
		_sevenv(info, "OLDPWD", _getenv(info, "PWD="));
		_sevenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
  * sh_help - display information about shell
  * @info: potentiel arguments
  *
  * Return: on sucess 0
  */
int sh_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("check help. function not implemented \n");
	if (0)
		_puts(*arg_array); /*value pointed*/
	return (0);
}
/**
  * sh_exit - exit the shell env
  * @info: potential arguments
  *
  * Return: 1 in error otherwise -2
  */
int sh_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* if exit arg exist */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "number doesnt exist");
			_eputs(info->argv[1]);
			_eputchar('\\');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
