## PIPEX :

Pipex reproduit le comportement du pipe en ligne de commande (shell)

On doit reproduire le fonctionnement de cette commande :

`< infile cmd1 | cmd2 > outfile`

Ça nous fait découvrir la différence entre les processus et les programmes, comment en tirer parti et aussi des fonctions comme pipe, fork, dup2, access et execve 

La problématique principale du projet de pipex elle dans la **gestion des processus et des redirections de flux d'entrée/sortie** pour reproduire le comportement des pipe en shell
