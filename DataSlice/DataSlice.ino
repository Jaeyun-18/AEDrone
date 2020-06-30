void setup() 
{
  Serial.begin(9600);
}

char a[30] = {'2','3','4','-','5','6','8','1','5','6','a','x','x','x','x','x','x','x','x','x','x','x'};
int i=0;
int cp = 0;
void loop()
{
  String str1="    ";
  String str2="   ";

  while(cp != 1)
  {
    if(48<=int(a[i]) && int(a[i])<=57)
    {
      for(int j=i; j<i+3; j++)
      {
        str2.setCharAt(j-i, a[j]);
      }
      
      int nR = str2.toInt();
      Serial.println(nR);
      str2 = "   ";
      i+=3;
    }
  
    if(a[i] == '-')
    {
      for(int j=i; j<i+4; j++)
      {
        str1.setCharAt(j-i, a[j]);
      }
      
      int nR = str1.toInt();
      Serial.println(nR);
      str1 = "    ";
      i+=4;
    }
  
    if(a[i] == 'a') cp=1;
  }
}
