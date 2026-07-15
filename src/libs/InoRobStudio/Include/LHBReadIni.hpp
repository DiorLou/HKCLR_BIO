/********************************************************************
 *@file   		文件名
 *@brief  		读INI配置文件
 *				详细描述
 *@note  		备注
 *@warning  		注意事项
 *@author 		梁和兵
 *@date 			2013-08-23
 *@version 		版本 1.0.0
 *@since 		修改说明
 ********************************************************************/

#ifndef LHB_READINI_HPP
#define LHB_READINI_HPP

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILE_SIZE 1024 * 16
#define LEFT_BRACE    '['
#define RIGHT_BRACE   ']'

class CLHBReadIni
{
public:
    CLHBReadIni()
    {
    }

    ~CLHBReadIni()
    {
    }

public:
    /**
     *@brief read string in initialization file\n
     * retrieves a string from the specified section in an initialization file
     *@param section [in] name of the section containing the key name
     *@param key [in] name of the key pairs to value
     *@param value [in] pointer to the buffer that receives the retrieved string
     *@param size [in] size of value buffer
     *@param default_value [in] defualt value of result
     *@param file [in] path of the initialization file
     *@return 1 : read success; \n 0 : read fail
     */
    int read_profile_string(const char *section, const char *key, char *value,
                            int size, const char *default_value, const char *file)
    {
        std::unique_ptr<char> buf(new char[MAX_FILE_SIZE]);
        memset(buf.get(), 0, MAX_FILE_SIZE);
        int file_size;
        int sec_s, sec_e, key_s, key_e, value_s, value_e;

        // check parameters
        assert(section != NULL && strlen(section));
        assert(key != NULL && strlen(key));
        assert(value != NULL);
        assert(size > 0);
        assert(file != NULL && strlen(key));

        if (!load_ini_file(file, buf.get(), &file_size))
        {
            if (default_value != NULL)
            {
                strncpy(value, default_value, size);
            }
            return 0;
        }

        if (!parse_file(section, key, buf.get(), &sec_s, &sec_e, &key_s, &key_e, &value_s, &value_e))
        {
            if (default_value != NULL)
            {
                strncpy(value, default_value, size);
            }
            return 0;  // not find the key
        }
        else
        {
            int cpcount = value_e - value_s;

            if (size - 1 < cpcount)
            {
                cpcount = size - 1;
            }

            memset(value, 0, size);
            memcpy(value, buf.get() + value_s, cpcount);
            value[cpcount] = '\0';

            return 1;
        }
    }

    /**
     *@brief int value in initialization file\n
     * retrieves int value from the specified section in an initialization file
     *@param section [in] name of the section containing the key name
     *@param key [in] name of the key pairs to value
     *@param default_value [in] defualt value of result
     *@param file [in] path of the initialization file
     *@return profile int value,if read fail, return default value
     */
    int read_profile_int(const char *section, const char *key, int default_value,
                         const char *file)
    {
        char value[32] = { 0 };
        if (!read_profile_string(section, key, value, sizeof(value), NULL, file))
        {
            return default_value;
        }
        else
        {
            return atoi(value);
        }
    }
    int write_profile_int(const char *section_pass, const char *key_pass_ini, const int value_pass, const char *file_pass)
    {
        char tmp[10] = { 0 };
        sprintf(tmp, "%d", value_pass);
        return write_profile_string(section_pass, key_pass_ini, tmp, file_pass);
    }
    /**
     * @brief write a profile string to a ini file
     * @param section [in] name of the section,can't be NULL and empty string
     * @param key [in] name of the key pairs to value, can't be NULL and empty string
     * @param value [in] profile string value
     * @param file [in] path of ini file
     * @return 1 : success\n 0 : failure
     */
    int write_profile_string(const char *section, const char *key, const char *value, const char *file)
    {
        std::unique_ptr<char> buf(new char[MAX_FILE_SIZE]);
        memset(buf.get(), 0, MAX_FILE_SIZE);
        std::unique_ptr<char> w_buf(new char[MAX_FILE_SIZE]);
        memset(w_buf.get(), 0, MAX_FILE_SIZE);
        int sec_s, sec_e, key_s, key_e, value_s, value_e;
        int value_len = (int)strlen(value);
        int file_size;
        FILE *out;

        // check parameters
        assert(section != NULL && strlen(section));
        assert(key != NULL && strlen(key));
        assert(value != NULL);
        assert(file != NULL && strlen(key));

        if (!load_ini_file(file, buf.get(), &file_size))
        {
            sec_s = -1;
        }
        else
        {
            parse_file(section, key, buf.get(), &sec_s, &sec_e, &key_s, &key_e, &value_s, &value_e);
        }

        if (-1 == sec_s)
        {
            if (0 == file_size)
            {
                sprintf(w_buf.get() + file_size, "[%s]\n%s=%s\n", section, key, value);
            }
            else
            {
                // not find the section, then add the new section at end of the file
                memcpy(w_buf.get(), buf.get(), file_size);
                sprintf(w_buf.get() + file_size, "\n[%s]\n%s=%s\n", section, key, value);
            }
        }
        else if (-1 == key_s)
        {
            // not find the key, then add the new key & value at end of the section
            memcpy(w_buf.get(), buf.get(), sec_e);
            sprintf(w_buf.get() + sec_e, "%s=%s\n", key, value);
            sprintf(w_buf.get() + sec_e + strlen(key) + strlen(value) + 2, buf.get() + sec_e, file_size - sec_e);
        }
        else
        {
            // update value with new value
            memcpy(w_buf.get(), buf.get(), value_s);
            memcpy(w_buf.get() + value_s, value, value_len);
            memcpy(w_buf.get() + value_s + value_len, buf.get() + value_e, file_size - value_e);
        }

        out = fopen(file, "w");
        if (NULL == out)
        {
            return 0;
        }

        if (-1 == fputs(w_buf.get(), out))
        {
            fclose(out);
            return 0;
        }

        fclose(out);
        return 1;
    }

private:
    int load_ini_file(const char *file, char *buf, int *file_size)
    {
        FILE *in = NULL;
        int i = 0;
        int ch = 0;
        *file_size = 0;

        assert(file != NULL);
        assert(buf != NULL);

        in = fopen(file, "r");
        if (NULL == in)
        {
            return 0;
        }

        // load initialization file
        while ((ch = fgetc(in)) != EOF)
        {
            if (i < MAX_FILE_SIZE - 1)
            {
                buf[i] = static_cast<char>(ch);
            }
            else
            {
                i++;
                break;
            }

            i++;
            assert(i < MAX_FILE_SIZE);  // file too big
        }
        buf[i] = '\0';
        *file_size = i;

        fclose(in);
        return 1;
    }
    int isnewline(char c)
    {
        return ('\n' == c || '\r' == c) ? 1 : 0;
    }
    int isend(char c)
    {
        return '\0' == c ? 1 : 0;
    }
    int isleftbarce(char c)
    {
        return LEFT_BRACE == c ? 1 : 0;
    }
    int isrightbrace(char c)
    {
        return RIGHT_BRACE == c ? 1 : 0;
    }
    int parse_file(const char *section, const char *key, const char *buf, int *sec_s, int *sec_e,
                   int *key_s, int *key_e, int *value_s, int *value_e)
    {
        const char *p = buf;
        int i = 0;

        assert(buf != NULL);
        assert(section != NULL && strlen(section));
        assert(key != NULL && strlen(key));

        *sec_e = *sec_s = *key_e = *key_s = *value_s = *value_e = -1;

        while (!isend(p[i]))
        {
            // find the section
            if ((0 == i || isnewline(p[i - 1])) && isleftbarce(p[i]))
            {
                int section_start = i + 1;

                // find the ']'
                do
                {
                    i++;
                }
                while (!isrightbrace(p[i]) && !isend(p[i]));

                if (0 == strncmp(p + section_start, section, i - section_start))
                {
                    int newline_start = 0;

                    i++;

                    // Skip over space char after ']'
                    while (isspace(p[i]))
                    {
                        i++;
                    }

                    // find the section
                    *sec_s = section_start;
                    *sec_e = i;

                    while (!(isnewline(p[i - 1]) && isleftbarce(p[i]))
                           && !isend(p[i]))
                    {
                        int j = 0;
                        // get a new line
                        newline_start = i;

                        while (!isnewline(p[i]) && !isend(p[i]))
                        {
                            i++;
                        }

                        // now i  is equal to end of the line
                        j = newline_start;

                        if (';' != p[j])  // skip over comment
                        {
                            while (j < i && p[j] != '=')
                            {
                                j++;
                                if ('=' == p[j])
                                {
                                    if (strncmp(key, p + newline_start, j - newline_start) == 0)
                                    {
                                        // find the key ok
                                        *key_s = newline_start;
                                        *key_e = j - 1;

                                        *value_s = j + 1;
                                        *value_e = i;

                                        return 1;
                                    }
                                }
                            }
                        }

                        i++;
                    }
                }
            }
            else
            {
                i++;
            }
        }
        return 0;
    }
};

#endif
