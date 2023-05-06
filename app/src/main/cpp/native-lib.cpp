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

class Solution {
public:

    void simplify(std::string& eval, int index, char type, bool restrictions = false)
    {
        // -(3+(4+5)) ---> -3-(4-5))

        for (int i = index; i < eval.size(); i++)
        {
            if (eval[i] == '-' && eval[i + 1] == '(')
            {
                if(eval[i+2] == '-')
                {
                    eval.erase(i+2, 1);
                    eval[i] = '+';
                }

                if(type == '-')
                    eval[index] = '+';

                eval.erase(i+1, 1);

                std::stack<char> st;
                int j = i+1;

                if(eval[j] == '(')
                    j--;


                st.push('(');

                while(!st.empty())
                {
                    if(eval[j] == '-' && eval[j+1] == '(')
                    {
                        simplify(eval, j, '-', 1);
                        st.push('(');
                    }
                    else if(eval[j] == '-' && eval[j+1] != '(')
                        eval[j] = '+';
                    else if(eval[j] == '+' && eval[j+1] == '(')
                    {
                        eval[j] = '-';
                        eval.erase(j+1, 1);
                        st.push('(');
                    } else if(eval[j] == '+' && eval[j+1] != '(')
                        eval[j] = '-';
                    else if(eval[j] == ')')
                    {
                        st.pop();
                        eval.erase(j,1);
                        if(restrictions)
                            i = eval.size();

                    }
                    else if(eval[j] == '(')
                        st.push('(');
                    j++;
                    std::cout << eval << std::endl;
                }
            }

        }

    }

    int calculate(std::string input)
    {
        //Define Variables
        std::string eval, numStr;
        int result = 0, num;

        //Simplify: remove spaces (easy part)
        for(auto i:input)
            if(i != ' ')
                eval+=i;

        //Simplify: remove parentheses (hard part)

        simplify(eval, 0, '+', false);

        //Simplify: remove parentheses(part 2) (easy part)

        for (int i = 0; i < eval.size(); i++)
            if(eval[i] == '(' || eval[i] == ')')
                eval.erase(i, 1);

        for (int i = 0; i < eval.size(); i++)
        {
            if(eval[i] == '+' && eval[i+1] == '-')
                eval.erase(i ,1);
            else if(eval[i] == '+' && eval[i+1] == '+')
                eval.erase(i,1);
            else if(eval[i] == '-' && eval[i+1] == '+')
                eval.erase(i+1,1);
            else if(eval[i] == '-' && eval[i+1] == '-')
            {
                eval.erase(i+1, 1);
                eval[i] == '+';
            }
        }

        //solve (medium part)
        if(eval[0] != '+' && eval[0] != '-')
            eval.insert(eval.begin(),'+');

        for (int i = 0; i < eval.size(); i++)
        {
            if(eval[i] == '+' || eval[i] == '-')
            {
                int k = i+1;

                while(k < eval.size() && isdigit(eval[k]))
                {
                    numStr+=eval[k];
                    k++;
                }
                num = std::stoi(numStr);
            }

            if(eval[i] == '+')
                result+=num;
            else if (eval[i] == '-')
                result-=num;

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
