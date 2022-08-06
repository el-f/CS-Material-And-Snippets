const { MongoClient, ServerApiVersion } = require('mongodb');

const cwd = process.cwd();

// read the connection string from 'connection_details.txt'
const connectionString = require('fs').readFileSync(cwd + '/Databases/NoSQL DBs/MongoDB/connection_details.txt', 'utf8');
const uri = connectionString.trim();

const client = new MongoClient(uri, { useNewUrlParser: true, useUnifiedTopology: true, serverApi: ServerApiVersion.v1 });
client.connect(async err => {
    const collection = client.db("sample_airbnb").collection("listingsAndReviews");

    const aggregation_pipline = [
        {
            '$match': {
                'price': {
                    '$lt': 500
                },
                'accommodates': {
                    '$gt': 4
                },
                'amenities': {
                    '$regex': RegExp('hair dryer'),
                    '$options': 'i'
                }
            }
        }, {
            '$sort': {
                'price': 1
            }
        }, {
            '$project': {
                'name': 1,
                'amenities': 1,
                'price': 1,
                'images': 1,
                'description': 1
            }
        }, {
            '$limit': 20
        }
    ];

    const query_result = await collection.aggregate(aggregation_pipline).toArray();

    console.log(query_result);


    client.close();
});