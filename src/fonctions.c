#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/declarations.h"
#include "../lib/stdout_color.h"

#define FILE_ACCESS "./doc/"

// Creation : Return NULL

tableLineType NewTableLine(){
	return NULL;
}
tableType NewTable(){
	return NULL;
}

tableType CreateFileData(char *fileName){
	/*
	char srcFileName[100] = "\0";
	char commandPrompt[100] = "\0";
	strcat(strcat(srcFileName, FILE_ACCESS), fileName);
	strcat(strcat(commandPrompt, "touch "), srcFileName);
	system(commandPrompt);
	//system("ls");

    return NULL;
	*/
	char srcFileName[100] = "\0";
	strcat(strcat(srcFileName, FILE_ACCESS), fileName);
	FILE *file_var = fopen(srcFileName, "wx");
	if(file_var == NULL){
		printf("File \"%s\" already exists\n", fileName);
		return NULL;
	}
	printf("Create file \"%s\"\n", fileName);
	fclose(file_var);
	return NULL;
}

/*
	IsNull : Return True if parameter point to NULL
	                 False if parameter do not point to NULL
*/

int IsNullTableLine(tableLineType tableLine){
	if(tableLine == NULL)
		return 1;
	else
		return 0;
}
int IsNullTable(tableType table){
	if(table == NULL)
		return 1;
	else
		return 0;
}

/*
	IsEmpty : Return True if parameter's lenght is 0
	                 False if parameter's lenght is not 0
*/

int IsEmptyTableLine(tableLineType tableLine){
	if(tableLine->lenght == 0)
		return 1;
	else
		return 0;
}
int IsEmptyTable(tableType table){
	if(table->lenght == 0)
		return 1;
	else
		return 0;
}

// Push

/*
// TODO Fixing this function by dividing it in 2, one to make the line, and the other to reduce it
*/
tableLineType PushBackTableLine(tableLineType tableLine, char *line){
	int i = 0;
	int j = 0;
	tableCellType *node = NULL;

	while(line[i] != '\0'){
		node = malloc(sizeof(tableCellType));

		node->back = NULL;
		node->next = NULL;
		node->lenght = 0;
		j = 0;
		
		while(line[i] != ';' && line[i] != '\n' && line[i] != '\0'){
			if(line[i] < 32);
			else{
				node->value[j] = line[i];
				node->lenght++;
				j++;
			}
			i++;
		}

		node->value[j] = '\0';
		if(line[i] != '\0'){
			i++;
		}

		if(IsNullTableLine(tableLine)){
			tableLine = malloc(sizeof(*tableLine));

			tableLine->lenght = 0;
			tableLine->begin = node;
			tableLine->end = node;
			tableLine->back = NULL;
			tableLine->next = NULL;
		}
		else if(IsEmptyTableLine(tableLine)){
			tableLine->lenght = 0;
			tableLine->begin = node;
			tableLine->end = node;
			tableLine->back = NULL;
			tableLine->next = NULL;
		}
		else{
			tableLine->end->next = node;
			node->back = tableLine->end;
			tableLine->end = node;
		}

		tableLine->lenght++;
	}

	while(tableLine->end->lenght == 0 /*|| tableLine->end->lenght == 1*/){
		node = tableLine->end;
		tableLine->end = tableLine->end->back;
		tableLine->end->next = NULL;
		tableLine->lenght--;
		ClearTableCell(node);
	}

	return tableLine;
}
/*
// TODO Deleting this because it makes no sense
*/
tableLineType PushBackTableLineBis(tableLineType tableLine, char *line){
	int i = 0;
	int j = 0;
	tableCellType *node = NULL;

	while(line[i] != '\0'){
		node = malloc(sizeof(tableCellType));

		node->back = NULL;
		node->next = NULL;
		node->lenght = 0;
		j = 0;
		
		while(line[i] != ';' && line[i] != '\n' && line[i] != '\0'){
			if(line[i] < 32);
			else{
				node->value[j] = line[i];
				node->lenght++;
				j++;
			}
			i++;
		}

		node->value[j] = '\0';
		if(line[i] != '\0'){
			i++;
		}

		if(IsNullTableLine(tableLine)){
			tableLine = malloc(sizeof(*tableLine));

			tableLine->lenght = 0;
			tableLine->begin = node;
			tableLine->end = node;
			tableLine->back = NULL;
			tableLine->next = NULL;
		}
		else if(IsEmptyTableLine(tableLine)){
			tableLine->lenght = 0;
			tableLine->begin = node;
			tableLine->end = node;
			tableLine->back = NULL;
			tableLine->next = NULL;
		}
		else{
			tableLine->end->next = node;
			node->back = tableLine->end;
			tableLine->end = node;
		}

		tableLine->lenght++;
	}

	return tableLine;
}
tableType PushBackTable(tableType table, tableLineType* tableLine){
	if(IsNullTable(table)){
		table = malloc(sizeof(*table));

		table->begin = *tableLine;
		table->end = *tableLine;
		table->lenght = 0;
		table->width = 0;
		table->cellWidth = NULL;
	}
	if(IsEmptyTable(table)){
		table->begin = *tableLine;
		table->end = *tableLine;
		table->lenght = 0;
		table->width = 0;
		table->cellWidth = NULL;
	}
	else{
		table->end->next = *tableLine;
		(*tableLine)->back = table->end;
		table->end = *tableLine;
	}
	table->lenght++;
	*tableLine = NULL;

	return table;
}

// Pull

//tableCellType* PullFrontTableLine(tableLineType tableLine);
//tableLineType PullFrontTable(tableType table);

// Clear

void ClearTableCell(tableCellType *tableCell){
	free(tableCell);
}
tableLineType ClearTableLine(tableLineType tableLine){
	tableCellType *buffer = NULL;
	if(tableLine == NULL)
		return NULL;
	else{
		tableLine->begin = NULL;
		while(tableLine->end != NULL){
			buffer = tableLine->end;
			tableLine->end = tableLine->end->back;
			tableLine->lenght--;
			ClearTableCell(buffer);
		}
		free(tableLine);
		return NULL;
	}
}
tableType ClearTable(tableType table){
	tableLineType buffer = NULL;
	if(table == NULL){
		return NULL;
	}
	else{
		table->begin = NULL;
		while(table->end != NULL){
			buffer = table->end;
			table->end = table->end->back;
			table->lenght--;
			buffer = ClearTableLine(buffer);
		}
		free(table);
		return NULL;
	}
}

// Information

void GetTableLenght(tableType table){
	tableLineType tableLine = table->begin;
	int i = 1;
	if(tableLine == NULL){
		table->lenght = 0;
	}
	else{
		while(tableLine != table->end){
			tableLine = tableLine->next;
			i++;
		}
		table->lenght = i;
	}
}
tableCellType* GetCellValue(tableType table, int line, int column){
	tableLineType tableLine = table->begin;
	tableCellType *tableCell = NULL;
	if(line >= table->lenght)
		return NULL;
	else{
		for(int i = 0; i < line; i++){
			tableLine = tableLine->next;
		}
		tableCell = tableLine->begin;
		if(column >= tableLine->lenght)
			return NULL;
		else{
			for(int i = 0; i < column; i++){
				tableCell = tableCell->next;
			}
			return tableCell;
		}
	}
}
tableCellType* CopyCell(tableCellType* cell){
	tableCellType *tableCell = malloc(sizeof(tableCellType));
	if(cell != NULL){
		strcpy(tableCell->value, cell->value);
		tableCell->lenght = cell->lenght;
	}
	else{
		strcpy(tableCell->value, "");
		tableCell->lenght = 0;
	}
	tableCell->back = NULL;
	tableCell->next = NULL;

	return tableCell;
}
tableLineType CreateTableLine(tableType table, int line, int* orderColumns, int nbColumns){
	tableLineType tableLine;
	tableLine = malloc(sizeof(*tableLine));

	tableLine->back = NULL;
	tableLine->next = NULL;
	tableLine->begin = NULL;
	tableLine->end = NULL;
	tableLine->lenght = 0;

	for(int i = 0; i < nbColumns; i++){
		if(tableLine->lenght == 0){
			tableLine->begin = CopyCell(GetCellValue(table, line, orderColumns[i]));
			tableLine->end = tableLine->begin;
			tableLine->lenght = 1;
		}
		else{
			tableLine->end->next = CopyCell(GetCellValue(table, line, orderColumns[i]));
			tableLine->end->next->back = tableLine->end;
			tableLine->end = tableLine->end->next;
			tableLine->lenght++;
		}
	}

	return tableLine;
}
tableType GetTable(tableType tables, char tableName[25][25]){
	char tableNameBuffer[29];
	tableType tableBuffer;
	tableBuffer = malloc(sizeof(*tableBuffer));
	tableBuffer->cellWidth = NULL;
	tableLineType tableLine = tables->begin;

	strcpy(tableNameBuffer, "");										// Modify the name of the table to print, entered by the user, to get the its equivalent in the file to read
	strcat(strcat(strcat(tableNameBuffer, "__"), tableName[0]), "__");	//

	tableBuffer->lenght = 0;

	int i = 0;																			// Get the line of the file at which the chosen table starts, or, if there is no table as the one
	while(i < tables->lenght && strcmp(tableLine->begin->value, tableNameBuffer) != 0){	// chosen by the user, exit the function with a NULL value
		tableLine = tableLine->next;													//
		i++;																			//
	}																					//
	if(i == tables->lenght){															//
		free(tableBuffer);																//
		return NULL;																	//
	}																					//

	if(tableLine->next == NULL || (tableLine->next->begin->value[0] == '_' && tableLine->next->begin->value[1] == '_')){
		tableBuffer->begin = NULL;
		tableBuffer->end = NULL;

		if(tableLine->back == NULL && tableLine->next != NULL){
			tables->begin = tables->begin->next;
			tables->begin->back = NULL;
			tableLine = ClearTableLine(tableLine);
		}
		else if(tableLine->back != NULL && tableLine->next == NULL){
			tables->end = tables->end->back;
			tables->end->next = NULL;
			tableLine = ClearTableLine(tableLine);
		}
		else if(tableLine->back != NULL && tableLine->next != NULL){
			tableLine->back->next = tableLine->next;
			tableLine->next->back = tableLine->back;
			tableLine = ClearTableLine(tableLine);
		}
		else{
			tables->begin = NULL;
			tables->end = NULL;
			tableLine = ClearTableLine(tableLine);
		}
	}
	else{
		tableLine = tableLine->next;														//
		tableBuffer->begin = tableLine;														// Defines the limits of the table chosen by the user inside the file
		while(strstr(tableLine->begin->value, "__") == NULL && tableLine->next != NULL){	//
			tableLine = tableLine->next;													//
		}																					//
		if(tableLine->next != NULL)															//
			tableLine = tableLine->back;													//
		tableBuffer->end = tableLine;														//

		tableLine = tableBuffer->begin->back;
		if(tableBuffer->begin->back->back == NULL && tableBuffer->end->next != NULL){
			tables->begin = tableBuffer->end->next;
			tableBuffer->end->next = NULL;
			tableBuffer->begin->back = NULL;
			tables->begin->back = NULL;
			tableLine = ClearTableLine(tableLine);
		}
		else if(tableBuffer->begin->back->back != NULL && tableBuffer->end->next == NULL){
			tables->end = tableBuffer->begin->back->back;
			tableBuffer->end->next = NULL;
			tableBuffer->begin->back = NULL;
			tables->end->next = NULL;
			tableLine = ClearTableLine(tableLine);
		}
		else if(tableBuffer->begin->back->back != NULL && tableBuffer->end->next != NULL){
			tableBuffer->begin->back->back->next = tableBuffer->end->next;
			tableBuffer->end->next->back = tableBuffer->begin->back->back;
			tableBuffer->begin->back = NULL;
			tableBuffer->end->next = NULL;
			tableLine = ClearTableLine(tableLine);
		}
		else{
			tableBuffer->begin->back = NULL;
			tables->begin = NULL;
			tables->end = NULL;
			tableLine = ClearTableLine(tableLine);
		}
	}

	/*
	tableBuffer->begin->back->next = tableBuffer->end->next;	// Separates the table chosen by the user from the rest of the file
	tableBuffer->end->next->back = tableBuffer->begin->back;	//
	tableBuffer->begin->back = NULL;							//
	tableBuffer->end->next = NULL;								//
	*/

	GetTableLenght(tables);				// Get the metadatas of the table chosen by the user
	GetTableWidth(tables);				//
	GetTableCellWidth(tables);			//

	GetTableLenght(tableBuffer);				// Get the metadatas of the table chosen by the user
	GetTableWidth(tableBuffer);					//
	GetTableCellWidth(tableBuffer);				//
	strcpy(tableBuffer->name, tableName[0]);	//

	return tableBuffer;
}
tableType GetAssortedTable(tableType tableBuffer, char tableArguments[25][25]){
	int nbArguments = 0;
	int nbColumns = 0;
	int iterator = 0;
	tableLineType tableLine;
	tableCellType *tableCell;

	if(tableBuffer == NULL){
		return NULL;
	}
	else if(tableBuffer->begin == NULL){
		return tableBuffer;
	}

	if(strcmp(tableArguments[0], "__ALLARGUMENTS__") == 0){			// Initialises nbArguments, allowing to know the numbers of columns to be printed
		nbArguments = 0;											//
	}																//
	else{															//
		while(strcmp(tableArguments[nbArguments], "__END__") != 0){	//
			nbArguments++;											//
		}															//
	}																//

	int *printColumn = malloc(sizeof(int) * nbArguments);	// Defines the table printColumn, allowing to know if a column is to be printed
	for(int i = 0; i < nbArguments; i++){					//
		printColumn[i] = -1;								//
	}														//
	
	if(nbArguments == 0){
		free(printColumn);

		return tableBuffer;
	}
	else{
	
		for(int i = 0; i < nbArguments; i++){															// Put in each cell of the printColumn table the corresponding number of the column to print
			tableLine = tableBuffer->begin;																// from the file
			tableCell = tableLine->begin;																//
			iterator = 0;																				// Initialises the table printColumn, allowing to know if a column is to be printed
			while(strcmp(tableArguments[i], tableCell->value) != 0 && iterator < tableBuffer->width){	//
				tableCell = tableCell->next;															//
				iterator++;																				//
			}																							//
			if(strcmp(tableArguments[i], tableCell->value) == 0){										//
				printColumn[i] = iterator;																//
			}																							//
		}																								//

		iterator = 0;											// Defines the table orderColumns, allowing to know in which order the columns are to be printed
		for(int i = 0; i < nbArguments; i++){					//
			if(printColumn[i] != -1){							//
				iterator++;										//
			}													//
		}														//
		nbColumns = iterator;									//
		int *orderColumns = malloc(sizeof(int) * nbColumns);	//

		iterator = 0;										// Initialises  the table orderColumns, allowing to know in which order the columns are to be printed
		for(int i = 0; i < nbArguments; i++){				//
			if(printColumn[i] != -1){						//
				orderColumns[iterator] = printColumn[i];	//
				iterator++;									//
			}												//
		}													//

		free(printColumn);
		
		tableType table;																	// Effectue une copie de tableBuffer dans table en ne gardant que les colonnes du tableau à garder
		table = malloc(sizeof(*table));														//
		table->lenght = tableBuffer->lenght;												//
		strcpy(table->name, tableBuffer->name);												//
		table->cellWidth = NULL;															//
		tableLine = tableBuffer->begin;														//
		table->begin = CreateTableLine(tableBuffer, 0, orderColumns, nbColumns);			//
		table->end = table->begin;															//
		for(int i = 1; i < table->lenght; i++){												//
			table->end->next = CreateTableLine(tableBuffer, i, orderColumns, nbColumns);	//
			table->end->next->back = table->end;											//
			table->end = table->end->next;													//
		}																					//
		GetTableLenght(table);																//
		GetTableWidth(table);																//
		GetTableCellWidth(table);															//

		free(orderColumns);

		return table;
	}
}
int GetLineLenght(tableType table, int line){
	tableLineType tableLine = table->begin;
	for(int i = 0; i < line; i++){
		tableLine = tableLine->next;
	}
	return tableLine->lenght;
}
void GetTableWidth(tableType table){
	table->width = 0;
	for(int i = 0; i < table->lenght; i++){
		if(GetLineLenght(table, i) > table->width){
			table->width = GetLineLenght(table, i);
		}
	}
}
void GetTableCellWidth(tableType table){
	if(table->cellWidth != NULL){
		free(table->cellWidth);
		table->cellWidth = NULL;
	}
	table->cellWidth = malloc(table->width * sizeof(int));
	tableCellType *tableCell = NULL;
	for(int i = 0; i < table->width; i++){
		table->cellWidth[i] = 0;
		for(int j = 0; j < table->lenght; j++){
			tableCell = GetCellValue(table, j, i);
			if(tableCell != NULL){
				if(tableCell->lenght > table->cellWidth[i]){
					table->cellWidth[i] = tableCell->lenght;
				}
			}
		}
	}
}

// Print

void PrintTable(tableType table){
	if(table != NULL){
		tableLineType tableLine = table->begin;
		tableCellType *tableCell = NULL;
		printf("============================================================\n");
		StdoutColorRed();
		printf("%s\n", table->name);
		StdoutColorReset();
		printf("============================================================\n");
		printf("\n");
		if(strcmp(table->name, "__ALLTABLES__") != 0){
			for(int i = 0; i < table->width; i++){
				printf("+");
				for(int j = 0; j < table->cellWidth[i]; j++){
					printf("-");
				}
			}
			printf("+\n");
			for(int i = 0; i < table->width; i++){
				tableCell = GetCellValue(table, 0, i);
				if (tableCell == NULL){
					printf("|");
					for (int j = 0; j < table->cellWidth[i]; j++)
						printf(" ");
				}
				else{
					printf("|");
					StdoutColorBlue();
					printf("%s", tableCell->value);
					StdoutColorReset();
					for (int j = 0; j < table->cellWidth[i] - tableCell->lenght; j++){
						printf(" ");
					}
				}
			}
			printf("|\n");
			for(int i = 0; i < table->width; i++){
				printf("+");
				for(int j = 0; j < table->cellWidth[i]; j++){
					printf("-");
				}
			}
			printf("+\n");
			for(int i = 1; i < table->lenght; i++){
				for(int j = 0; j < table->width; j++){
					tableCell = GetCellValue(table, i, j);
					if(tableCell == NULL){
						printf("|");
						for(int k = 0; k < table->cellWidth[j]; k++)
							printf(" ");
					}
					else{
						printf("|%s", tableCell->value);
						for(int k = 0; k < table->cellWidth[j] - tableCell->lenght; k++){
							printf(" ");
						}
					}
				}
				printf("|\n");
				tableLine = tableLine->next;
			}
			for(int i = 0; i < table->width; i++){
				printf("+");
				for(int j = 0; j < table->cellWidth[i]; j++){
					printf("-");
				}
			}
			printf("+\n");
		}
		else{
			for(int i = 0; i < table->lenght; i++){
				for(int j = 0; j < table->width; j++){
					tableCell = GetCellValue(table, i, j);
					if(tableCell == NULL){
						printf("[");
						for(int k = 0; k < table->cellWidth[j]; k++)
							printf(" ");
						printf("] ");
					}
					else{
						printf("[%s", tableCell->value);
						for(int k = 0; k < table->cellWidth[j] - tableCell->lenght; k++){
							printf(" ");
						}
						printf("] ");
					}
				}
				printf("\n");
				tableLine = tableLine->next;
			}
		}
	}
}
void ToPrint(char action[25], char tableName[25][25], char tableArguments[25][25], tableType table){
	tableLineType tableLine = table->begin;
	//tableCellType *tableCell = tableLine->begin;

	printf("\naction : %s\n", action);
	printf("table : %s\n", tableName[0]);
	printf("arguments : ");
	for(int i = 0; strcmp(tableArguments[i], "__END__") != 0 && i < 25; i++){
		printf("%s ", tableArguments[i]);
	}
	printf("\n");
	if(table != NULL){
		printf("table lenght : %d\n", table->lenght);
		printf("table width : %d\n", table->width);
		for(int i = 0; i < table->lenght; i++){
			printf("table line %d lenght : %d\n", i, tableLine->lenght);
			tableLine = tableLine->next;
		}
		for(int i = 0; i < table->width; i++){
			printf("column %d : %d\n", i, table->cellWidth[i]);
		}
	}
}
void PrintError(){
	printf("Erreur(s) dans le code\n");
}
void PrintHelp(){
	char line[1000];

	printf("============================================================\n");
	printf("Aide d'utilisation\n");
	printf("============================================================\n");
	printf("\n");
	FILE *fic = fopen("fics/help.txt", "r");
	if(fic == NULL){
		exit(1);
	}
	fseek(fic, 0, SEEK_SET);
	while(!feof(fic)){
		fgets(line, 500, fic);
		printf("%s", line);
	}
	fclose(fic);
}
void PrintStart(){
	char line[1000];

	FILE *fic = fopen("fics/start.txt", "r");
	if(fic == NULL){
		exit(1);
	}
	fseek(fic, 0, SEEK_SET);
	system("clear");
	while(!feof(fic)){
		fgets(line, 500, fic);
		printf("%s", line);
	}
	printf("\n");
	fclose(fic);
}






tableType GetFileData(tableType table, char *fileName){
	tableLineType tableLine = NewTableLine();
	char fileLineBrut[500];
	char fileLineBuffer[500];
	char srcFileName[100] = "\0";
	strcat(strcat(srcFileName, FILE_ACCESS), fileName);
	FILE *fic = fopen(srcFileName, "r");
	if(fic == NULL){
		exit(1);
	}
	fseek(fic, 0, SEEK_SET);
	while(!feof(fic)){
		fgets(fileLineBrut, 500, fic);
		if(strcmp(fileLineBuffer, fileLineBrut) != 0){
			tableLine = PushBackTableLine(tableLine, fileLineBrut);
			table = PushBackTable(table, &tableLine);
			strcpy(fileLineBuffer, fileLineBrut);
		}
	}
	fclose(fic);
	strcpy(table->name, "__ALLTABLES__");
	GetTableWidth(table);
	GetTableCellWidth(table);

	return table;
}
tableType CreateFileTable(tableType table, char tableName[25][25]){
	char tableNameBuffer[29];
	tableLineType tableLine = NewTableLine();
	strcpy(tableNameBuffer, "\0");
	strcat(strcat(strcat(tableNameBuffer, "__"), tableName[0]), "__\0");
	tableLine = PushBackTableLine(tableLine, tableNameBuffer);
	table = PushBackTable(table, &tableLine);
	return table;
}
void SetFileData(tableType table, char *fileName){
	tableLineType tableLine = NewTableLine();
	tableCellType *tableCell = NULL;
	char srcFileName[100] = "\0";
	strcat(strcat(srcFileName, FILE_ACCESS), fileName);
	FILE *fic = fopen(srcFileName, "w");
	if(fic == NULL){
		exit(1);
	}
	tableLine = table->begin;
	tableCell = tableLine->begin;
	for(int i = 0; i < table->lenght; i++){
		for(int j = 0; j < table->width; j++){
			if(tableCell != NULL){
				fprintf(fic, "%s", tableCell->value);
				tableCell = tableCell->next;
			}
			else{

			}

			if(j != table->width - 1){
				fprintf(fic, ";");
			}
			else{

			}
		}
		fprintf(fic, "\n");
		tableLine = tableLine->next;
		if(tableLine != NULL){
			tableCell = tableLine->begin;
		}
	}
	fclose(fic);
}
tableType CreateFileTableColumn(tableType tableBuffer, char tableArguments[25][25]){
	tableLineType tableLine = tableBuffer->begin;
	
	for(int i = 0; strcmp(tableArguments[i], "__END__") != 0; i++){
		tableLine = PushBackTableLine(tableLine, tableArguments[i]);
	}

	return tableBuffer;
}
tableType CreateFileTableLine(tableType tableBuffer, char tableArguments[25][25], char tableValues[25][25], int tableSize){
	int *tableIndexes = NULL;
	tableIndexes = malloc(sizeof(*tableIndexes)*tableSize);

	for(int i = 0; i < tableSize; i++){
		tableIndexes[i] = -1;
	}

	for(int i = 0; i < tableSize; i++){
		for(int j = 0; j < tableBuffer->width; j++){
			if(strcmp(tableArguments[i], GetCellValue(tableBuffer, 0, j)->value) == 0){
				tableIndexes[i] = j;
			}
		}
	}

	for(int i = 0; i < tableSize; i++){
		if(tableIndexes[i] == -1){
			PrintError();
			return tableBuffer;
		}
	}

	char *tempString;
	tempString = malloc(sizeof(*tempString) * tableBuffer->width);

	for(int i = 0; i < tableBuffer->width; i++){
		strcat(tempString, ";");
	}

	tableLineType tableLine;

	tableLine = PushBackTableLineBis(tableLine, tempString);

	free(tempString);

	tableBuffer = PushBackTable(tableBuffer, &tableLine);

	for(int i = 0; i < tableSize; i++){
		strcpy(GetCellValue(tableBuffer, tableBuffer->lenght - 1, tableIndexes[i])->value, tableValues[i]);
	}

	free(tableIndexes);

	return tableBuffer;
}
tableType SetTable(tableType tables, tableType tableBuffer){
	char tableNameBuffer[29];
	tableLineType tableLine = NewTableLine();

	strcpy(tableNameBuffer, "\0");
	strcat(strcat(strcat(tableNameBuffer, "__"), tableBuffer->name), "__\0");
	tableLine = PushBackTableLine(tableLine, tableNameBuffer);
	tables = PushBackTable(tables, &tableLine);
	tables->end->next = tableBuffer->begin;
	tableBuffer->begin->back = tables->end;
	tables->end = tableBuffer->end;

	tableBuffer->begin = NULL;
	tableBuffer->end = NULL;
	
	GetTableLenght(tables);
	GetTableWidth(tables);
	GetTableCellWidth(tables);

	GetTableLenght(tableBuffer);
	GetTableWidth(tableBuffer);
	GetTableCellWidth(tableBuffer);

	return tables;
}