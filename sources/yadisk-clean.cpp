using yadisk::ops::Resource;
using yadisk::ops::Predicate;
using yadisk::ops::Tree;
using yadisk::Client;
using std::string;
using std::map;
 
using Resources = std::vector<Resource>;
 
namespace yadisk 
{
  namespace ops 
  {
      /**
      Выполняет поиск копий данных на диске
      \param[in] client ссылка на client-yadisk
      \param[in] Hash булева функция сравнения параметров
      \return возвращает ресурсы всех копий данных
      **/
      map<string, Resources> find_duplicate(Client& client, Predicate pred = Hash)
      {	
             map<string, Resources> resultFind; 

             Resources  listAllFiles = client.list();

             struct {
              bool operator()(Resource a, Resource b) const
              {  
                  return a.md5 < b.md5;
              }  
              } customLessResource;

             std::sort(listAllFiles.begin(), listAllFiles.end(), customLessResource);

             Resource curEdge = listAllFiles.first;	
             Resources curEdgeCopies;

             for(int i = 0; i < listAllFiles.size(); ++i)
             {
                  string curEdgeMD5 = curEdge.md5;
                  string md5 = listAllFiles[i].md5;	

                  if(curEdgeMD5   == md5)
                   curEdgeCopies.push_back(listAllFiles[i]);
                  else
                  {
                      addCopiesInResult(curEdgeCopies, resultFind);

                      curEdge = listAllFiles[i];
                      curEdgeCopies.clear();
                  }	
            }	
            return resultFind;
      }
      /**
      Выполняет поиск копий данных на диске
      \param[in] curEdgeCopies ресурсы копий данных на диске
      \param[in] resultFind результат сравнения данных
      **/
      void addCopiesInResult(Resources curEdgeCopies, map<string, Resources>& resultFind)
      {
          for(int i = 0; i < curEdgeCopies.size(); ++i)
          resultFind[curEdgeCopies[i].path].insert(curEdgeCopies);
      }
  }
}
