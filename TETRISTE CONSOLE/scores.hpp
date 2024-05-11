#ifndef SCORE

#define SCORE

#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "cJSON.h"

using namespace std;

class JsonSerializable
{
protected:
    string filename;
    string root;

public:
    JsonSerializable(const string &filename, const string &root) : filename(filename), root(root) {}

    virtual cJSON *toJSON() const = 0;

    void saveToFile() const
    {
        string fullPath = root + "/" + filename;
        cJSON *json = toJSON();
        if (json)
        {
            char *jsonStr = cJSON_Print(json);
            if (jsonStr)
            {
                ofstream file(fullPath);
                if (file.is_open())
                {
                    file << jsonStr;
                    //cout << "Data saved to file: " << fullPath << endl;
                }
                else
                {
                    cerr << "Failed to open file: " << fullPath << endl;
                }
                cJSON_free(jsonStr);
            }
            else
            {
                cerr << "Failed to convert JSON to string." << endl;
            }
            cJSON_Delete(json);
        }
        else
        {
            cerr << "Failed to create JSON object." << endl;
        }
    }

    void clearFile() const
    {
        string fullPath = root + "/" + filename;
        ofstream file(fullPath, ofstream::trunc); // Open file in truncate mode to clear existing data
        if (file.is_open())
        {
            file.close();
            //cout << "File cleared: " << fullPath << endl;
        }
        else
        {
            cerr << "Failed to open file: " << fullPath << endl;
        }
    }
};

class Score : public JsonSerializable
{
private:
    struct PlayerScore
    {
        string playerName;
        long int score;

        // Constructeur pour initialiser le nom du joueur et son score
        PlayerScore(const string &name, long int s) : playerName(name), score(s) {}
    };

    // Utilisation d'un vecteur de PlayerScore au lieu d'une map pour stocker les scores
    vector<PlayerScore> scoreList;

public:
    // Constructor to initialize from an existing JSON file, if it exists
    Score(const string &filename, const string &root = ".") : JsonSerializable(filename, root)
    {
        loadFromFile();
    }

    // M�thode pour trier les scores par ordre d�croissant
    void sortScores()
    {
        // Utilisation d'une lambda pour sp�cifier l'ordre de tri
        auto comparator = [](const PlayerScore &a, const PlayerScore &b) {
            return a.score > b.score; // Ordre d�croissant
        };

        // Tri du vecteur scoreList en utilisant le comparateur
        sort(scoreList.begin(), scoreList.end(), comparator);
    }

    // M�thode pour ajouter un score
    void addScore(const string &playerName, long int score)
    {
        scoreList.push_back(PlayerScore(playerName, score));
        sortScores(); // Tri des scores apr�s l'ajout
        saveToFile(); // Mise � jour du fichier JSON
    }

    // M�thode pour afficher les scores
    void showScores() const
    {
        for (const auto &score : scoreList)
        {
            cout << score.playerName << ": " << score.score << endl;
        }
    }

    // M�thode pour afficher les dix premiers scores
    void show10Scores() const
    {
        int count = 0;
        for (const auto &score : scoreList)
        {
            cout << score.playerName << ": " << score.score << endl;
            count++;
            if (count >= 10) // Limite � 10 scores affich�s
                break;
        }
    }


    // Impl�mentation toJSON modifi�e pour refl�ter le changement de structure de donn�es
    cJSON *toJSON() const override
    {
        cJSON *json = cJSON_CreateObject();
        cJSON *scoresArray = cJSON_CreateArray();
        for (const auto &score : scoreList)
        {
            cJSON *scoreObj = cJSON_CreateObject();
            cJSON_AddStringToObject(scoreObj, "playerName", score.playerName.c_str());
            cJSON_AddNumberToObject(scoreObj, "score", score.score);
            cJSON_AddItemToArray(scoresArray, scoreObj);
        }
        cJSON_AddItemToObject(json, "scores", scoresArray);
        return json;
    }

    // M�thode pour charger les scores depuis un fichier JSON
    void loadFromFile()
    {
        string fullPath = root + "/" + filename;
        ifstream file(fullPath);
        if (file.is_open())
        {
            string jsonStr((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
            cJSON *json = cJSON_Parse(jsonStr.c_str());
            if (json)
            {
                cJSON *scoresArray = cJSON_GetObjectItem(json, "scores");
                if (scoresArray && cJSON_IsArray(scoresArray))
                {
                    cJSON *scoreItem = nullptr;
                    cJSON_ArrayForEach(scoreItem, scoresArray)
                    {
                        const char *playerName = cJSON_GetObjectItem(scoreItem, "playerName")->valuestring;
                        long int score = cJSON_GetObjectItem(scoreItem, "score")->valuedouble; // Utilisation de valuedouble pour les nombres
                        scoreList.push_back(PlayerScore(playerName, score));
                    }
                }
                cJSON_Delete(json);
            }
            file.close();
        }
    }
};


#endif // SCORE
