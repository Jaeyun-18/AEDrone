void setup() 
{
  Serial.begin(9600);
}

char a[30] = {'2','3','4','-','5','6','8','1','5','6','a','x','x','x','x','x','x','x','x','x','x','x'};
int i=0;
void loop()
{

  String str1="    ";
  String str2="   ";

  if(48<=int(a[i]) && int(a[i])<=57)
  {
    for(int j=i; j<i+3; j++)
    {
      str2.setCharAt(a, a[j]);
    }
    char cTempData[3];
    str2.substring(0, 3).toCharArray(cTempData, 3);
    int nR = atoi(cTempData);
    str2 = "   ";
    i+=3;
  }

  if(a[i] == '-')
  {
    for(int j=i; j<i+4; j++)
    {
      str1.setCharAt(a, a[j]);
    }
    char cTempData[4];
    str1.substring(0, 4).toCharArray(cTempData, 4);
    int nR = atoi(cTempData);
    str1 = "    ";
    i+=4;
  }
}
