minimize z:
	2*x['x1'] + x['x2'] + 3*x['x4'] - x['x5'] + 4*x['x6'] + x['x7'] + 
	x['x8'];

subject to v1['r1']:
	x['x1'] - x['x2'] - x['x3'] + x['x8'] <= 80;

subject to v1['r2']:
	x['x4'] + x['x5'] + x['x6'] - x['x7'] <= 60;

subject to v2['r3']:
	x['x1'] + x['x4'] >= 60;

subject to v2['r5']:
	x['x3'] + x['x6'] >= 20;

subject to v3['r4']:
	x['x2'] + x['x5'] = 40;

subject to vj1['x1']:
	x['x1'] >= 0;

subject to vj1['x2']:
	x['x2'] >= 0;

subject to vj1['x4']:
	x['x4'] >= 0;

subject to vj1['x6']:
	x['x6'] >= 0;

subject to vj1['x7']:
	x['x7'] >= 0;

subject to vj1['x8']:
	x['x8'] >= 0;

subject to vj2['x5']:
	x['x5'] <= 0;

