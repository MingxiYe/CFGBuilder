//
// Created by Shall on 2021/11/2.
//

#ifndef CFGCONSTRUCTION_TOOLS_H
#define CFGCONSTRUCTION_TOOLS_H

#endif //CFGCONSTRUCTION_TOOLS_H
class Tools {
    wstring s2ws(const string& str) {
        if (str.empty()) {
            return L"";
        }
        unsigned len = str.size() + 1;
        setlocale(LC_CTYPE, "en_US.UTF-8");
        wchar_t *p = new wchar_t[len];
        mbstowcs(p, str.c_str(), len);
        std::wstring w_str(p);
        delete[] p;
        return w_str;
    }

public :
    int32_t hashCode(const string& str) {
        int32_t h = 0;
        //SoDebug("strlength is: %u",str.length());
        std::wstring wstr=s2ws(str);
        //SoDebug("wstr.length is %u",wstr.length());
        if (h == 0 && wstr.length() > 0) {
            for (uint32_t i = 0; i < wstr.length(); i++) {
                h = 31 * h + wstr.at(i);
            }
        }
        return h;
    }

};
