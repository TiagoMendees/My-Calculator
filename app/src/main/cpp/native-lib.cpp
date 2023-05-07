#include <jni.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;

class Solution
{
public:

    const bool Continue(string str)
    {
        for(auto i:str)
            if(i == '/' || i == '*')
                return true;
        return false;
    }

    int calculate(string input)
    {
        // Define Variables
        std::string numStr, eval;
        int result = 0, num;

        // Simplify: remove spaces (easy part)
        for (auto i : input)
            if (i != ' ')
                eval += i;

        for (int i = 0; i < eval.size(); i++)
            if(eval[i] == 'x')
                eval[i] = '*';


        // solve multiplications and divisions(Hard part)

        redo:

        for (int i = 0; i < eval.size(); i++)
        {
            if (eval[i] == '/' || eval[i] == '*')
            {
                string prev, next;

                int size2 = 0;

                for (int j = i + 1; j < eval.size(); j++) //2*3+1
                {
                    if (!isdigit(eval[j]))
                    {
                        j = eval.size();
                    }
                    else
                    {
                        next += eval[j];
                        size2++;
                    }
                }

                eval.erase(i+1, size2);

                int size = 0, start = 0;

                for (int j = i - 1; j >= 0; j--)
                {
                    if (!isdigit(eval[j]))
                    {
                        start = j + 1;
                        break;
                    }
                    else
                    {
                        prev += eval[j];
                        size++;
                    }
                }

                reverse(prev.begin(), prev.end());

                int res;

                if (eval[i] == '*')
                    res = stoi(prev) * stoi(next);
                else
                    res = stoi(prev) / stoi(next);

                string str = to_string(res);

                eval.insert(i+1, str);
                eval.erase(start, size+1);

                cout << eval << endl;
                i = eval.size();
            }
        }

        if(Continue(eval))
            goto redo;

        if (eval[0] != '+' && eval[0] != '-')
            eval.insert(eval.begin(), '+');

        for (int i = 0; i < eval.size(); i++)
        {
            if (eval[i] == '+' || eval[i] == '-')
            {
                int k = i + 1;

                while (k < eval.size() && isdigit(eval[k]))
                {
                    numStr += eval[k];
                    k++;
                }
                num = std::stoi(numStr);
            }

            if (eval[i] == '+')
                result += num;
            else if (eval[i] == '-')
                result -= num;

            numStr = "";
        }

        return result;
    }
};

std::string jstring2string(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_nytrostudios_mycalculator_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_nytrostudios_mycalculator_MainActivity_calc(JNIEnv *env, jobject thiz, jstring str) {

    Solution SL;
    std::string input = jstring2string(env, str);

    return env->NewStringUTF(std::to_string(SL.calculate(input)).c_str());
}
