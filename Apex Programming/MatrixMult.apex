public class MatrixMult {
	public void Mult(List<List<Integer>> matrix)
        {
            Integer mult = 1;
            for(Integer i=0;i<matrix.size();i++)
            {
                for(Integer j=0;j<matrix[i].size();j++)
                {
                    mult *= matrix[i][j];
                }
            }
            System.debug('Multiplication is : ' + mult);
        }
}

List<List<Integer>> matrix = new List<List<Integer>> ();
matrix.add(new List<Integer> {1,2,3});
matrix.add(new List<Integer> {1,2,3});
matrix.add(new List<Integer> {1,2,3});
MatrixMult m = new MatrixMult();
m.Mult(matrix);