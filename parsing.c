#include "parsing.h"

static int Depth = 0;

void pathInit () {
    Path = calloc(1, sizeof(PtList));
}

void pathFree () {
    if(Path) {
        free(Path -> Point);
        free(Path -> Date);
        free(Path -> Height);
        free(Path);
    }
}

void startElement (void *Data, const char *Element, const char **Attribute) {
    if(!strcmp(Element, "trkpt")) {
        Path -> Point = realloc(Path -> Point, (Path -> pointsNum + 1) * sizeof(Pt));
        Path -> Point[Path -> pointsNum].lat = atofC(Attribute[1]);
        Path -> Point[Path -> pointsNum].lon = atofC(Attribute[3]);
        Path -> pointsNum++;
    }
    Depth++;
}

void endElement (void *Data, const char *Element) {
    Depth--;
}

void Handler(void *Data, const char *Object, int Length) {
    if(Depth == 5) {
        if(Object[Length + 2] == 't') {
            char dateCheck[4];
            strncpy(dateCheck, Object + Length + 2, 4);
            if(!strcmp(dateCheck, "time")) {
                char dateStr [Length];
                strncpy(dateStr, Object, Length);
                Path -> Date = realloc(Path -> Date, (Path -> dateNum + 1) * sizeof(PtDate));
                getDate(Path -> Date, Path -> dateNum, dateStr);
                Path -> dateNum++;
            }
        }
        else if(Object[Length + 2] == 'e'){
            char heightStr [Length];
            strncpy(heightStr, Object, Length);
            Path -> Height = realloc(Path -> Height, (Path -> hNum + 1) * sizeof(double));
            Path -> Height[Path -> hNum] = atofC(heightStr);
            Path -> hNum++;
        }
    }
}

bool PathParse (const char *fileName) {
    FILE *fp;
    
    if((fp = fopen(fileName, "r")) == NULL) {
        return 0;
    }

    pathInit();
    char *Buff = malloc(BUFF_SIZE);

    XML_Parser Parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(Parser, startElement, endElement);
    XML_SetCharacterDataHandler(Parser, Handler);

    fread(Buff, sizeof(char), BUFF_SIZE, fp);

    XML_Parse(Parser, Buff, strlen(Buff), XML_TRUE);

    fclose(fp);
    free(Buff);
    XML_ParserFree(Parser);

    return 1;
}