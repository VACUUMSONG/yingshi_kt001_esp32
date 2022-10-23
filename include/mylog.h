//
// Created by wt on 0017.
//

#ifndef SMARTCAR_MYLOG_H
#define SMARTCAR_MYLOG_H

#define LOG_ENABLE 1
#if LOG_ENABLE
#define mylog(format,...) printf(format"\r\n",##__VA_ARGS__)
#else
#define mylog(format,...)
#endif

#endif //SMARTCAR_MYLOG_H
