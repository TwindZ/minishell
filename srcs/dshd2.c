#include "../include/minishell.h"

void	dshd2_init(t_data *data)
{
	ft_bzero(&data->dshd2, sizeof(dshd2));
}

int	dollar(char *line)
{
	int i;

	i = 0;
	while(line[i++])
	{
		if(line[i] == '$')
			return (1);
	}
	return (0);

}

char	*get_var()

void dshd2(t_data *data)
{
	char *templine;
	char *vardata;
	char *var;
	int i;
	int j;
	int	varlen;

	varlen = 0;
	j = 0;
	i = 0;
	templine = ft_strdup(data->readhd);
	
	while(dollar(templine))
	{
		if(templine[i++] == '$')
		{
			while(templine[i++] != " ")
				varlen++
			while(templine[i--] != '$')
				;
			var = ft_calloc(varlen, sizeof(char));
			var = ft_strncpy(templine[i], &var, varlen);

		}
	}

}