
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bst.h"


void insert_word(TreeNode** root, const char *word)
{
	if(*root == NULL)
	{
		*root = (TreeNode*)malloc(sizeof(TreeNode));
		unsigned int len = strlen(word);
		(*root)->word = (char *)malloc((len + 1) * sizeof(char));
		strncpy((*root)->word, word, len);
		(*root)->word[len] = 0;
		(*root)->frequency = 1;
		(*root)->left = NULL;
		(*root)->right = NULL;
	}
	else
	{
		int compare = strcasecmp(word, (*root)->word);
		if(compare <0)
		{
			insert_word(&((*root)->left), word);
		}
		else if(compare> 0)
		{
			insert_word(&((*root)->right), word);
		}
		else if(compare == 0)
		{
			(*root)->frequency++;
		}
	}
}

void traverse_tree(const TreeNode* root)
{
	if(root == NULL)
		return;
	if(root != NULL)
	{
		traverse_tree(root->left);
		printf("%s %d\n", root->word, root->frequency);
		traverse_tree(root->right);
	}
	return;
}


void cleanup_tree(TreeNode* root)
{
	if(root == NULL)
		return;
	if(root->left != NULL)
	{
		cleanup_tree(root->left);
	}
	if(root->right != NULL)
	{
		cleanup_tree(root->right);
	}	
	free(root->word);
	free(root);

	return;
}

int main(int argc, char* argv[])
{
	if(argc > 1)
		printf("Usage: bst");
	else
	{
		FILE* pFile = fopen("input.1", "r");
		char *buf = NULL;
		size_t len = 0;
		TreeNode** root = NULL;
		if(!pFile)
		{
			printf("File not found");
		}
		else
		{
			root = (TreeNode**)malloc(sizeof(TreeNode*));
			*root = NULL;
			while(getline(&buf,&len,pFile) > 0)
			{
				//printf("%s", buf);
				char * pch;
				pch = strtok(buf, " !@#$%^&*?.,:;\n");
				while(pch !=NULL)
				{
					insert_word(root, pch);
					pch = strtok(NULL, " !@#$%^&*,:;?.\n"); 
				}
				//free(buf);
				//free(pch);
			}
			free(buf);
			fclose(pFile);
			traverse_tree(*root);
		}
		cleanup_tree(*root);
		free(root);
		
	}
	return 0;	
}
