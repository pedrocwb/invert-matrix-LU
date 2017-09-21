# Invert Square Matrix using LU decomposition
C program to invert a given square matrix using LU decomposition, Gauss-sidel with partial pivoting and refinement 

 ## Usage
    - make command to compile all files
    - ./invmat -i N [-r N] [-e in_file] -[o out_file]
    - -i N: is the refinement iterations
    - 

 ## TODO: 
 - Parser dos comandos da linha de comando
    - Mudar comando -i para -e para receber entrada viar arquivo
    - Salvar matriz no arquivo
    - Ler matriz da stdin
    - Imprimir resultado na stdout
 - Validar se a matriz é inversivel 
 - Implementar refinamento
 - Implementar a medição de tempo
 - Implementar a geração de matrizes aleatórias
 - Implementar os comentários dyoxigen
  ## FIXME:
 - ✓ [DONE] Função LU_decomposition: Esqueci de implementar o pivotamento do vetor b onde (Ax = b)
 - melhorar backward and forward substitution
 - 
 





