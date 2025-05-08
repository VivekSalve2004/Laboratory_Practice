public class MatrixAdd {
		public void Add(List<List<Integer>> matrix)
        {
            Integer sum = 0;
            for(Integer i=0;i<matrix.size();i++)
            {
                for(Integer j=0;j<matrix[i].size();j++)
                {
                    sum += matrix[i][j];
                }
            }
            System.debug('Sum is : ' + sum);
        }
}


List<List<Integer>> matrix = new List<List<Integer>> ();
matrix.add(new List<Integer> {1,2,3});
matrix.add(new List<Integer> {1,2,3});
matrix.add(new List<Integer> {1,2,3});
MatrixAdd m = new MatrixAdd();
m.Add(matrix);