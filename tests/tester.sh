cp mand/0_compare_parsing.sh ~/.minishellrc
cd ..
mkdir result/
bash tests/mand/0_compare_parsing.sh > result/bash_result
make && ./bin/minishell > result/minishell_result
diff result/minishell_result result/bash_result