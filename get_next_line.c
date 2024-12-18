/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:18:42 by alejaro2          #+#    #+#             */
/*   Updated: 2024/12/18 19:40:33 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *updated_accumulated(char *accumulated)
{
    char *ptr;
    char *temp;
    int len;
    int i;
    ptr = ft_strchr(accumulated, '\n');
    if (ptr != NULL)
        len = ft_strlen(ptr + 1);
    else
        len = 0;
    if (len == 0)
        return NULL;
    temp = malloc((len + 1) * sizeof(char));
    if (!temp)
        return(NULL);
    ptr++;
    i = 0;
    while (i < len){
        temp[i] = ptr[i];
        i++;
    }
    temp[i] = '\0';
    return(temp); 
}
char *extract_line (char *accumulated)
{
    char *ptr;
    char *line;
    int len;
    int i;

    ptr = ft_strchr(accumulated, '\n');
    if (ptr != NULL){
      len = ptr - accumulated;  
    }
    else{
      len = ft_strlen(accumulated);
    }
    line = malloc((len + 1) * sizeof(char));
    if (!line)
        return(NULL);
    i = 0;
    while (i < len){
        line[i] = accumulated[i];
        i++;
    }
    line[i] = '\0';
    return(line);
}

char *read_until(int fd, char **accumulated) 
{
    char *buffer;
    ssize_t bytes;

    if(!*accumulated){
        *accumulated = malloc(1 * sizeof(char));
        *accumulated[0] = '\0';
    }
    if(!*accumulated)
        return(NULL);
    buffer = (char *)malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (free(*accumulated), NULL);
    bytes = 1;
    while (ft_strchr(*accumulated, '\n') == NULL && bytes != 0){
        bytes = read(fd, buffer, BUFFER_SIZE);
        if(bytes == -1)
            return((free(*accumulated), free(buffer), NULL));
        buffer[bytes] = '\0';
        *accumulated = ft_strjoin(*accumulated, buffer);
        if(!*accumulated)
            return(free(buffer), NULL);
    }
    return(free(buffer), *accumulated);
    
}

char *get_next_line(int fd)
{
    static char *accumulated;
    char *line;
    char *temp;
    
    if(fd < 0 || BUFFER_SIZE <= 0)
        return(NULL);
    accumulated = read_until(fd, &accumulated);
    line = extract_line(accumulated); 
    temp = updated_accumulated(accumulated);
    free(accumulated);
    accumulated = temp;
    return(line);
}
int main() {
    int fd = open("hola.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    char *line;

    while (line = get_next_line(fd) != NULL)
    {
        printf("hola?\n%s\n", line);
        free(line);
    }
    //printf("%s\n", line = get_next_line(fd));
    //printf("%s\n", line = get_next_line(fd));
    // printf("%s\n", line = get_next_line(fd));
    // printf("%s\n", line = get_next_line(fd));
    // printf("%s\n", line = get_next_line(fd));
    // if(line != NULL)
    //free(line);
    close(fd);
    return (0);
}