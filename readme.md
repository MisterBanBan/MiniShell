nkermani:
✅ -echo -n cause un invalide read
✅ -echo "-n " ne devrai pas déclencher l'argument -n --> Done by fixing how struct is built, adding a bool to flag if there were quotes before hand.
✅ -"    ls" fonctionne au lieu de mettre commande not found
✅export " | " doit correspondre en gardant les espaces.
✅ -export a puis export a= cause une segmentation fault

✅-cd no_such_file_or_directory return 0 et non 1
✅-unset d'une variable vide
✅-les redirections ne fonctionnent pas avec les built-in


-la commande "" crée un child  --> Invalid command, ne doit pas passer dans la partie exec ensuite. ?



afavier:
-echo $?a n'afficher pas le a
-ctrl + c dans un  here doc affiche un message d'erreur
-'$?' expand le $?
-$PATHa supprime le a meme avec le $?
-les caractères tel que '|' dans des quote peuvent générer des erreurs de syntaxe
-une redirection ne contenant que des caractère numérique ne fonctionne pas