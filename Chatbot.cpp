#include <iostream>
#include <string>
#include <list>
#include <fstream>



class words
{
    private :
    std::list<std::string> m_sentenceList;
    std::list<std::string> m_totalWords;


    int m_sencence_counter; 
    static const int m_sentenceSize = 1000;
    int m_wordsNumb;
    std::string m_sentence[m_sentenceSize];
    std::string m_storedWords[m_sentenceSize];
    public :

    words()
    {   
        m_wordsNumb =  0;
        loadWords();
    }
    void talk(std::string sentence)
    {
        sentenceSplitt(sentence);
        storeWords();
    }


    void sentencePrint()
    {
        for(int i = 0;i < m_wordsNumb; i++)
        {
            std::cout <<"Word nr :" << i <<" is :" << m_storedWords[i] <<std::endl;
        }
    }

    void storeWords()
    {
        
        for(int i = 0;i < m_sencence_counter;i++)
        {
            bool neword = true;
            for(int e = 0; e < m_wordsNumb; e++)
            {
                if (m_sentence[i] == m_storedWords[e])
                {
                    neword = false;
                }
            }
            if (neword == true)
            {
                m_storedWords[m_wordsNumb] = m_sentence[i];
                m_wordsNumb++;
                std::cout <<"added :" << m_sentence[i] << " to known Words." << std::endl;
            }
        }
    }
    void saveWords()
    {
        std::ofstream filer;
        filer.open("words.txt", std::ofstream::out);
        
        for(int i = 0; i < m_wordsNumb; i++)
        {
            filer << m_storedWords[i] << std::endl;
        }
        std::cout << "sucessfully stored words to file !" << std::endl;
        filer.close();
    }
    void loadWords()
    {
        std::ifstream filer;
        filer.open("words.txt");
        int i = 0;

        while(getline(filer,m_storedWords[i]))
        {
            i++;
            m_wordsNumb++;
        }
        filer.close();
        std::cout << "sucessfully loaded words from file !" << std::endl;
    }


    void sentenceSplitt(std::string line)
    {
        m_sencence_counter = 0;
        std::string cut_line_x = line;
        std::string worder;
        int x1 = 0;
        bool done = false;
        while(done == false)
        {
            x1 = cut_line_x.find_first_of(' ');

            if(x1 != std::string::npos)
            {
                worder = cut_line_x.substr(0,x1);
                cut_line_x = cut_line_x.substr(x1+1);
            }
            else
            {
                worder = cut_line_x;
                done = true;
            }
            //std::cout << "worder :" << worder <<std::endl;
            m_sentence[m_sencence_counter] = worder;
            m_sencence_counter++;
        }
    }

};


int main()
{
    words Asterix;
    bool exit = false;
    while(exit == false)
    {
        std::string say;
        std::getline(std::cin, say);
        Asterix.talk(say);
        if(say == "exit")
        exit = true;
    }
    Asterix.sentencePrint();
    Asterix.saveWords();
}
